// $Id: klayer.c,v 1.2 2002/08/13 17:30:38 Administrator Exp $

#include "mem.h"

#include "klayer.h"
#include "shav.h"

static int initted = 0;
void k_layer_init( void )
{
  if (initted)
    return;

  initted = 1;
}

klayer *k_new_klayer( void )
{
  klayer *nk;

  A(initted);

  nk = NEW(klayer);
  nk->map = make_shav_hash();
  nk->prev = 0;

  return nk;
}

void k_layer_put( klayer *kl, char *name, kvalue value )
{
  A(initted);

  A(kl);
  A(kl->map);
  put_hash( kl->map, name, make_shav_obj( (void*)value ) );
}

kvalue k_layer_get( klayer *kl, char *name )
{
  shav *v;

  A(initted);

  A(kl);
  A(kl->map);

  v = get_hash( kl->map, name );

  if (v==0)
    return KV_NIL;

  MUSTOBJ(v);
  return (kvalue)get_obj( v );
}

int k_layer_contains( klayer *kl, char *name )
{
  A(initted);

  A(kl);
  A(kl->map);
  return hash_contains( kl->map, name );
}

void k_dump_layer( klayer *kl )
{
  A(initted);

  A(kl);
  shav_dump( kl->map );
}

klayer *k_layer_get_prev( klayer *kl )
{
  A(kl);
  return kl->prev;
}

void k_layer_set_prev( klayer *kl, klayer *prev )
{
  A(kl);
  kl->prev = prev;
}

int k_layer_size( klayer *kl )
{
  A(kl);
  A(kl->map);
  return HASHSIZE(kl->map);
}
