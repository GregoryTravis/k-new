// $Id: kvalue.c,v 1.3 2002/08/21 16:03:51 Administrator Exp $

#include <stdio.h>

#include "a.h"
#include "mem.h"
#include "spew.h"

#include "katom.h"
#include "kvalue.h"

#define KV_GOOD_POINTER(p) ((((int)(p)) & KV_TAG_BIT_MASK)==0)

static int kvalue_initted = 0;

void kv_dump_1( FILE *stream, kvalue value, int inlist );

void kvalue_shav_obj_dumper( FILE *file, void *obj )
{
  kvalue value = (kvalue)obj;

  A(KV_OK(value));

  kv_dump_1( file, value, 0 );
}

void k_value_init( void )
{
  if (kvalue_initted)
    return;

  shav_install_obj_dumper( &kvalue_shav_obj_dumper );

  kvalue_initted = 1;
}

/* This function is memoized via katom.c!! */
kvalue kv_mkatom( char *name )
{
  kvalue_atom *atom;

  atom = katom_get_atom( name );
  if (atom!=0)
    return (kvalue)atom;

  atom = malik( sizeof( kvalue_atom ) );
  A(KV_GOOD_POINTER(atom));
  atom->type = KATOM;
  atom->name = strdoop( name );

  katom_put_atom( name, atom );

  return (kvalue)atom;
}

kvalue kv_mkcons( kvalue car, kvalue cdr )
{
  kvalue_cons *cons;

  cons = malik( sizeof( kvalue_cons ) );
  A(KV_GOOD_POINTER(cons));

  cons->type = KCONS;
  cons->car = car;
  cons->cdr = cdr;

  return (kvalue)cons;
}

kvalue kv_mkclosure( klayer *env, shav *code )
{
  kvalue_closure *closure;

  closure = malik( sizeof( kvalue_closure ) );
  A(KV_GOOD_POINTER(closure));

  closure->type = KCLOSURE;
  closure->env = env;
  closure->code = code;

  return (kvalue)closure;
}

void kv_dump_1( FILE *stream, kvalue value, int inlist )
{
  A(stream);
  A(value);

  if (value==KV_NIL) {
    fprintf( stream, "()" );
  }

  switch( KV_TYPE(value) ) {
    case KINT:
      fprintf( stream, "%d", KV_GET_INT( value ) );
      break;
    case KFLOAT:
      fprintf( stream, "%f", KV_GET_FLOAT( value ) );
      break;
    case KATOM:
      {
        kvalue_atom *atom = KV_GET_ATOM(value);
        A(atom);
        A(atom->name);
        fprintf( stream, "%s", atom->name );
      }
      break;
    case KCONS:
      {
        kvalue car = KV_CAR( value );
        kvalue cdr = KV_CDR( value );

        if (!inlist)
          fprintf( stream, "(" );

        if (KV_ATOMIC( cdr )) {
          kv_dump_1( stream, car, 0 );
          fprintf( stream, " . " );
          kv_dump_1( stream, cdr, 1 );
          fprintf( stream, "_" );
        } else {
          kv_dump_1( stream, car, 0 );
          fprintf( stream, " " );
          kv_dump_1( stream, cdr, 1 );
        }
      }
      break;
    case KCLOSURE:
      {
        kvalue_closure *closure;
        shav *code, *args;

        closure = KV_GET_CLOSURE( value );
        A(closure);

        code = closure->code;
        A(code);

        args = get_hash( code, "args" );
        A(args);
        
        fprintf( stream, "#<closure" );

        if (closure->name) {
          fprintf( stream, " \"%s\"", closure->name );
        }

        FORVEC(args,i,arg,{
          fprintf( stream, " %s", get_string( arg ) );
        });

        fprintf( stream, ">" );
      }
      break;
    default:
      err(( "Bad value %x\n", value ));
      break;
  }
}

void kv_dump( kvalue value )
{
  kv_dump_1( stderr, value, 0 );
  fprintf( stderr, "\n" );
}

void kv_set_closure_name( kvalue closure, char *name )
{
  A(KV_OK(closure));
  A(KV_CLOSUREP(closure));

  ((kvalue_closure*)closure)->name = name;
}
