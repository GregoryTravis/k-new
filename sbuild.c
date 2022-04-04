// $Id: sbuild.c,v 1.4 2002/08/29 23:23:55 Administrator Exp $

#include <stdarg.h>

#include "mem.h"

#include "sparse.h"
#include "sbuild.h"

typedef struct compiled {
  char *format;
  sexp template;
} compiled ;

int n_compileds = 0;
compiled **compileds = NULL;

SEXP_STATIC_SYMBOL(percent,%);

static int count_blanks( sexp s )
{
  if (SEXP_IS_SYMBOL(s)) {
    return STR(s)[0]=='%' ? 1 : 0;
  } else if (SEXP_IS_CONS(s)) {
    return count_blanks( car( s ) ) + count_blanks( cdr( s ) );
  } else {
    return 0;
  }
}

compiled *sexp_build_compile( char *format )
{
  compiled *cmp;

  cmp = (compiled*)malik( sizeof(compiled) );
  cmp->format = format;
  cmp->template = sexp_parse( format );

  return cmp;
}

compiled *sexp_find_build_compiled( char *format )
{
  int i;

  if (compileds) {
    for (i=0; i<n_compileds; ++i) {
      if (compileds[i]->format==format) {
        return compileds[i];
      }
    }
  }

  if (compileds) {
    compileds = (compiled **)realik( compileds, sizeof(*compileds)*++n_compileds );
  } else {
    compileds = (compiled **)malik( sizeof(*compileds)*++n_compileds );
  }

  compileds[n_compileds-1] = sexp_build_compile( format );
  return compileds[n_compileds-1];
}

static sexp build_from_template( sexp s, va_list *va )
{
  switch( SEXP_TYPE(s) ) {
    case SEXP_NIL:
    case SEXP_INTEGER:
    case SEXP_HASH:
    case SEXP_OBJ:
    case SEXP_BOOLEAN:
      return s;
      break;
    case SEXP_SYMBOL:
      if (EQ(percent,s)) {
        sexp value = va_arg( *va, sexp );
        A(SEXP_OK(value));
        return value;
      } else {
        return s;
      }
      break;
    case SEXP_CONS:
      {
        sexp a, d;
        a = build_from_template( car( s ), va );
        d = build_from_template( cdr( s ), va );
        return cons( a, d );
      }
      break;
    default:
      err(( "build_from_template: Bad sexp type %d\n", SEXP_TYPE( s ) ));
      break;
  }
  A(0);
  return nil;
}

sexp sexp_build( char *format, ... )
{
  sexp built;
  compiled *cmp;
  va_list va;

  va_start( va, format );

  cmp = sexp_find_build_compiled( format );
  A(cmp);

  // build the struct!
  built = build_from_template( cmp->template, &va );

  va_end( va );

  return built;

}

static int scan_from_template( sexp target, sexp s, va_list *va )
{
  switch( SEXP_TYPE( s ) ) {
    case SEXP_NIL:
    case SEXP_INTEGER:
    case SEXP_HASH:
    case SEXP_OBJ:
      return EQ(target,s);
      break;
    case SEXP_SYMBOL:
      if (EQ(percent,s)) {
        sexp *value = va_arg( *va, sexp * );
        A(value);
        *value = target;
        return 1;
      } else {
        return EQ(target,s);
      }
      break;
    case SEXP_CONS:
      if (SEXP_IS_CONS( target )) {
        return 
          scan_from_template( car( target ), car( s ), va ) &&
          scan_from_template( cdr( target ), cdr( s ), va );
      } else {
        return 0;
      }
      break;
    default:
      printf( "target " );
      sexp_dump( target );
      printf( "s " );
      sexp_dump( s ); 
      err(( "scan_from_template: Bad sexp type %d\n", SEXP_TYPE( s ) ));
      break;
  }
  A(0);
  return 0;
}

int sexp_scan( sexp target, char *format, ... )
{
  int num;
  compiled *cmp;
  va_list va;

  va_start( va, format );

  cmp = sexp_find_build_compiled( format );
  A(cmp);

  num = scan_from_template( target, cmp->template, &va );

  va_end( va );

  return num;
}
