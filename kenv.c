// $Id: kenv.c,v 1.7 2002/10/22 19:16:48 Administrator Exp $

#include "kenv.h"
#include "kerr.h"

/*
  Env structure:

  ((layer (name . value) (name . value)...)
   (layer (name . value) (name . value)...)
   (layer (name . value) (name . value)...)
   (layer (name . value) (name . value)...))
*/

sexp kenv_make_env( void )
{
  return sexp_build( "((layer))" );
}

static sexp get_env_pair( sexp env, sexp name )
{
  sexp layers;

  A(SEXP_OK(env));
  A(SEXP_OK(name)&&SEXP_IS_SYMBOL(name));

  layers = env;

  while (layers != nil) {
   sexp pair;

   A(SEXP_OK(layers));

   pair = assoc( name, cdr( car( layers ) ) ); 

   if (SEXP_IS_CONS(pair)) {
      return pair;
    }
    layers = cdr( layers );
  }

  //SD( env );
  kerrw( name, "Unknown variable '%s'", STR(name) );
  return nil;
}

sexp kenv_get_env( sexp env, sexp name )
{
  sexp pair = get_env_pair( env, name );

  KERRPUNTV(nil);

  return cdr( pair );
}

void kenv_put_env( sexp env, sexp name, sexp value )
{
  sexp pair = get_env_pair( env, name );

  KERRPUNT;

  setcdr( pair, value );
}

static void add_pair_to_layer( sexp layer, sexp pair )
{
  A(SEXP_OK(layer));
  A(SEXP_OK(pair));
  A(EQ(car(layer),S(layer)));

  setcdr( layer, cons( pair, cdr( layer ) ) );
}

static sexp get_last_layer( sexp env )
{
  if (env==nil) {
    err(( "Can't get last layer of nil" ));
    return nil;
  } else if (SEXP_IS_CONS(env)) {
    if (cdr( env )==nil) {
      return car( env );
    } else {
      return get_last_layer( cdr( env ) );
    }
  } else {
    err(( "Can't get last layer of type %d", SEXP_TYPE(env) ));
    return nil;
  }
}

void kenv_global_put_env( sexp env, sexp name, sexp value )
{
  sexp global = get_last_layer( env );
  sexp pair;

  pair = assoc( name, cdr( global ) );

  if (pair = nil) {
    add_pair_to_layer( global, cons( name, value ) );
  } else {
    setcdr( pair, value );
  }
}

sexp kenv_add_layer( sexp env, sexp layer )
{
  A(SEXP_OK(env));
  A(SEXP_OK(layer));

  return cons( cons( S(layer), layer ), env );
}

#if 0
sexp kenv_make_env( void )
{
  return nil;
}

void kenv_put_env( sexp env, sexp name, sexp value )
{
  A(SEXP_OK(env));
  A(SEXP_OK(name));
  A(SEXP_OK(value));
  A(SEXP_IS_SYMBOL(name));

  if (SEXP_IS_NIL( env )) {
    kerr( "Unknown variable %s\n", STR(name) );
    return;
  } else {
    sexp alist = car( env );
    sexp p = assoc( name, alist );
    if (p==nil) {
      return kenv_put_env( cdr( env ), name, value );
    } else {
      setcdr( p, value );
      return;
    }
  }
}

sexp kenv_get_env( sexp env, sexp name )
{
  A(SEXP_OK(env));
  A(SEXP_OK(name));
  A(SEXP_IS_SYMBOL(name));

  if (SEXP_IS_NIL( env )) {
    kerr( "Unknown variable %s\n", STR(name) );
  } else {
    sexp alist = car( env );
    sexp p = assoc( name, alist );
    if (p==nil) {
      return kenv_get_env( cdr( env ), name );
    } else {
      return cdr( p );
    }
  }
  return nil;
}

sexp kenv_get_layer( sexp env, int which )
{
  if (which==0) {
    if (SEXP_IS_CONS( env )) {
      return car( env );
    } else {
      err(( "Can't get env layer" ));
      return nil;
    }
  } else {
    if (SEXP_IS_CONS( env )) {
      return kenv_get_layer( cdr( env ), which-1 );
    } else {
      err(( "Can't get env layer" ));
      return nil;
    }
  }
}

void kenv_set_layer( sexp env, int which, sexp layer )
{
  if (which==0) {
    A(SEXP_IS_CONS( env ));
    setcar( env, layer );
  } else {
    kenv_set_layer( cdr( env ), which-1, layer );
  }
}

sexp kenv_add_whole_layer( sexp env, sexp layer )
{
  return cons( layer, env );
}

sexp kenv_add_layer( sexp env, sexp params, sexp args )
{
  return kenv_add_whole_layer( env, zipper( params, args ) );
}

sexp kenv_add_to_layer( sexp layer, sexp name, sexp value )
{
  return cons( cons( name, value ), layer );
}

sexp kenv_make_layer( void )
{
  return nil;
}
#endif
