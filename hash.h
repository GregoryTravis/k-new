/* $Id: hash.h,v 1.2 2005/02/18 20:56:18 greg Exp $ */

#ifndef _hash_h_
#define _hash_h_

struct hash;
typedef struct hash hash;

#include "dexp.h"

typedef struct hashentry
{
  dexp key;
  dexp value;
  struct hashentry *next;
} hashentry;

struct hash {
  int size;
  int num_entries;
  hashentry **entries;
} ;

hash *makehash( int size );
void hashput( hash *h, dexp key, dexp value );
dexp hashget( hash *h, dexp key );
void hashdel( hash *h, dexp key );

typedef struct hashiter {
  hash *h;
  int index;
  hashentry *cursor;
} hashiter ;

void hash_init_iter( hashiter *hi, hash *h );
int hash_iter_next( hashiter *hi, dexp *key, dexp *value );
void hash_dump( hash *h );

#define FORHASH(__h,__k,__v) \
  dexp __k;\
  dexp __v;\
  hashiter __k##iter;\
  hash_init_iter( &__k##iter, (__h) );\
  while (hash_iter_next( &__k##iter, &__k, &__v ))

#endif /* _hash_h_ */
