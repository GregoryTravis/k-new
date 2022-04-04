// $Id: klayer.h,v 1.2 2002/08/13 17:30:38 Administrator Exp $

#ifndef _klayer_h_
#define _klayer_h_

#include "shav.h"

#include "kstruct.h"
#include "kvalue.h"

typedef struct klayer {
  shav *map;
  struct klayer *prev;
} klayer ;

void k_layer_init( void );
klayer *k_new_klayer( void );
void k_layer_put( klayer *kl, char *name, kvalue value );
kvalue k_layer_get( klayer *kl, char *name );
int k_layer_contains( klayer *kl, char *name );
void k_dump_layer( klayer *kl );
klayer *k_layer_get_prev( klayer *kl );
void k_layer_set_prev( klayer *kl, klayer *prev );
int k_layer_size( klayer *kl );

#endif /* _klayer_h_ */
