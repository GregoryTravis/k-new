// $Id: sexp.c,v 1.19 2002/10/22 20:33:19 Administrator Exp $

#include <stdarg.h>

#include "fstrm.h"
#include "mem.h"
#include "sexp.h"
#include "spew.h"
#include "strm.h"
#include "sstrm.h"

#define INDENT_STEP (2)
#define PP_LINE_LEN (25)

static int (*obj_dumper)( ostrm *ost, void *stuff ) = 0;

sexp_heap _nil = { SEXP_NIL, NULL, CONST_NIL };
sexp nil = (sexp)&_nil;

SEXP_STATIC_SEXP(true,SEXP_BOOLEAN);
SEXP_STATIC_SEXP(false,SEXP_BOOLEAN);

static sexp_heap *new_sexp_heap( void )
{
  sexp_heap *sh = malik( sizeof( sexp_heap ) );

  A(!(((int)sh)&SEXP_TAG_BIT_MASK)); // must have tag bits empty

  sh->properties = nil;

  return sh;
}

sexp cons( sexp car, sexp cdr )
{
  sexp_heap *pair;

  A(SEXP_OK(car));
  A(SEXP_OK(cdr));

  pair = new_sexp_heap();
  pair->type = SEXP_CONS;
  pair->contents.cons.car = car;
  pair->contents.cons.cdr = cdr;

  return (sexp)pair;
}

sexp mkobj( void *obj )
{
  sexp_heap *nu;

  nu = new_sexp_heap();

  nu->type = SEXP_OBJ;
  nu->contents.obj.obj = obj;

  return (sexp)nu;
}

sexp mknative( sexp_native native, char *funcname )
{
  sexp_heap *nu;

  nu = new_sexp_heap();

  nu->type = SEXP_NATIVE;
  nu->contents.native.native = native;
  nu->contents.native.funcname = funcname;

  return (sexp)nu;
}

sexp mkclosure( sexp code, sexp env, char *name )
{
  sexp_heap *nu;

  nu = new_sexp_heap();

  nu->type = SEXP_CLOSURE;
  nu->contents.closure.code = code;
  nu->contents.closure.env = env;
  nu->contents.closure.name = name;

  return (sexp)nu;
}

sexp mkstring( char *string )
{
  sexp_heap *nu;

  nu = new_sexp_heap();

  nu->type = SEXP_STRING;
  nu->contents.string.string = string;

  return (sexp)nu;
}

static void pprint( ostrm *ost, sexp s, int indent, int *advance, int *did_newline, int oneline );

static void print_spaces( ostrm *ost, int n )
{
  while( n-- )
    stputc( ' ', ost );
}

// indent: the number of chars we should indent after a newline
// advance: the number of chars we have printed on this line
static void pprint( ostrm *ost, sexp s, int indent, int *advance, int *did_newline, int oneline )
{
  A(SEXP_OK(s));
  A(advance);

  switch( SEXP_TYPE( s ) ) {
    case SEXP_NIL:
      stprintf( ost, "()" );
      *advance += 2;
      break;
    case SEXP_SYMBOL:
      {
        char *name = STR( s );
        A(name);
        stprintf( ost, "%s", name );
        *advance += strlen( name );
      }
      break;
    case SEXP_INTEGER:
      {
        int i = SEXP_GET_INTEGER( s ), c=0;
        stprintf( ost, "%d", i );
        while (i>0) {
          c+=2;
          i>>=2;
        }
        *advance += c;
      }
      break;
    case SEXP_CONS:
      {
        int did_newline_r = 0;
        int lcount = 0;
        sexp ss = s;

        indent += 2;

        stputc( '(', ost );
        (*advance)++;

        while (1) {
          int do_newline = !oneline && (did_newline_r || lcount>=2) && SEXP_IS_CONS( ss );

          if (do_newline) {
            stputc( '\n', ost );
            print_spaces( ost, indent );
            *advance = indent;
            *did_newline = 9;
          }

          if (!do_newline) {
            if (lcount>0 && !SEXP_IS_NIL( ss )) {
              stputc( ' ', ost );
              (*advance)++;
            }
          }

          if (SEXP_IS_NIL( ss )) {
            stputc( ')', ost );
            (*advance)++;
            break;
          } else if (SEXP_IS_CONS( ss )) {
            pprint( ost, car( ss ), indent, advance, &did_newline_r, oneline );
          } else {
            stputc( '.', ost );
            stputc( ' ', ost );
            *advance += 2;
            pprint( ost, ss, indent, advance, &did_newline_r, oneline );
            stputc( ')', ost );
            (*advance)++;
            break;
          }

          lcount++;
          ss = cdr( ss );
        }
      }
      break;
    case SEXP_HASH:
      *advance += stprintf( ost, "#<hash 0x%x>", (void*)s );
      break;
    case SEXP_OBJ:
      if (obj_dumper) {
        *advance += (*obj_dumper)( ost, SEXP_GET_OBJ( s ) );
      } else {
        *advance += stprintf( ost, "#<object 0x%x>", (void*)s );
      }
      break;
    case SEXP_NATIVE:
      {
        char *name = SEXP_GET_NATIVE_FUNCNAME( s );
        stprintf( ost, "#<prim %s>", name );
        *advance += 8;
        *advance += strlen( name );
      }
      break;
    case SEXP_CLOSURE:
      {
        char *name = SEXP_GET_CLOSURE_NAME( s );

        *advance += 10;

        stprintf( ost, "#<closure" );
        if (name != NULL) {
          stprintf( ost, " %s", name );
          *advance += strlen( name )+1;
        } else {
          *advance += stprintf( ost, " 0x%x", (void*)s );
        }
//stprintf( ost, " " );
//pprint( ost, SEXP_GET_CLOSURE_CODE( s ), indent, advance, did_newline, oneline );
        stprintf( ost, ">" );
      }
      break;
    case SEXP_BOOLEAN:
      stprintf( ost, "%s", s==true ? "#t" : "#f" );
      *advance += 2;
      break;
    case SEXP_STRING:
      stprintf( ost, "\"%s\"", SEXP_GET_STRING(s) );
      *advance += SEXP_STRING_LENGTH(s)+2;
      break;
    default:
      err(( "pprint: Bad sexp type %d\n", SEXP_TYPE( s ) ));
      break;
  }
}

void sexp_pp_stream( ostrm *ost, sexp s, int oneline )
{
  int dummy=0, dummy2=0;

  pprint( ost, s, 0, &dummy, &dummy2, oneline );
}

static ostrm *stdout_stream = 0;
static ostrm *get_stdout_stream( void )
{
  if (stdout_stream==0) {
    stdout_stream = ofstrm_create_from_stream( stdout );
  }

  return stdout_stream;
}

void sexp_pp( sexp s )
{
  sexp_pp_stream( get_stdout_stream(), s, 0 );
}

void sexp_dump_stream( FILE *stream, sexp s )
{
  ostrm *ost;

  ost = ofstrm_create_from_stream( stream );

  sexp_pp_stream( ost, s, 0 );
  stputc( '\n', ost );
}

void sexp_dump( sexp s )
{
  sexp_dump_stream( stdout, s );
}

void sexp_dump_file( char *filename, sexp s )
{
  ostrm *ost;

  ost = ofstrm_create( filename );
  A(ost);

  sexp_pp_stream( ost, s, 0 );
  stputc( '\n', ost );

  ostrm_close( ost );
}

char *sexp_dump_string( sexp s )
{
  ostrm *ost;

  ost = osstrm_create();

  sexp_pp_stream( ost, s, 1 );

  return osstrm_get( ost );
}

void sexp_install_obj_dumper( int (*dumper)( ostrm *ost, void *stuff ) )
{
  obj_dumper = dumper;
}

sexp mksym( char *name )
{
  sexp_heap *nu;

  nu = new_sexp_heap();

  nu->type = SEXP_SYMBOL;
  nu->contents.symbol.name = name;

  return (sexp)nu;
}

int length( sexp list )
{
  if (SEXP_IS_NIL( list )) {
    return 0;
  } else if (SEXP_IS_CONS( list )) {
    return length( cdr( list ) )+1;
  } else {
    return 1;
  }
}

sexp append( sexp lyst1, sexp lyst2 )
{
  if (SEXP_IS_NIL( lyst1 )) {
    return lyst2;
  } else if (SEXP_IS_CONS( lyst1 )) {
    return cons( car( lyst1 ), append( cdr( lyst1 ), lyst2 ) );
  } else {
    SD(lyst1);
    err(( "Can't append lyst1" ));
    return nil;
  }
}

sexp snoc( sexp rdc, sexp rac )
{
  return append( rdc, cons( rac, nil ) );
}

sexp assoc( sexp key, sexp alist )
{
  if (SEXP_IS_NIL( alist )) {
    return nil;
  } else if (SEXP_IS_CONS( alist )) {
    if (EQ( key, caar( alist ) )) {
      return car( alist );
    } else {
      return assoc( key, cdr( alist ) );
    }
    return nil;
  } else {
    err(( "bad alist" ));
    return nil;
  }
  return nil;
}

void setcar( sexp pair, sexp car )
{
  A(SEXP_OK(pair));
  A(SEXP_OK(car));

  if (SEXP_IS_CONS( pair )) {
    car( pair ) = car;
  } else {
    sexp_dump( pair );
    err(( "not a pair!" ));
  }
}

void setcdr( sexp pair, sexp cdr )
{
  A(SEXP_OK(pair));
  A(SEXP_OK(cdr));

  if (SEXP_IS_CONS( pair )) {
    cdr( pair ) = cdr;
  } else {
    sexp_dump( pair );
    err(( "not a pair!" ));
  }
}

sexp zipper( sexp cars, sexp cdrs )
{
  if (SEXP_IS_NIL( cars ) != SEXP_IS_NIL( cdrs )) {
    err(( "Can't zipper!" ));
    return nil;
/*
    if (SEXP_IS_NIL( cars )) {
      return cdrs;
    } else {
      return cars;
    }
*/
  } else if (SEXP_IS_NIL( cars )) {
    return nil;
  } else {
    return cons( cons( car( cars ), car( cdrs ) ),
      zipper( cdr( cars ), cdr( cdrs ) ) );
  }
}

void sexp_dump_fancy( char *message, sexp sexp )
{
  printf( "---- %s ---------------------------------\n", message );
  sexp_dump( sexp );
  printf( "---- %s ---------------------------------\n", message );
}

sexp caar( sexp s )
{
  s = car( s );
  s = car( s );
  return s;
}

sexp cadr( sexp s )
{
  s = cdr( s );
  s = car( s );
  return s;
}

sexp cdar( sexp s )
{
  s = car( s );
  s = cdr( s );
  return s;
}

sexp cddr( sexp s )
{
  s = cdr( s );
  s = cdr( s );
  return s;
}

sexp caddr( sexp s )
{
  s = cdr( s );
  s = cdr( s );
  s = car( s );
  return s;
}
