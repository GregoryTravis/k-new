/* $Id: hash.c,v 1.2 2005/02/18 20:56:18 greg Exp $ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "a.h"
#include "hash.h"
#include "mem.h"

hash *makehash( int size )
{
  A(size>0);
  hash *h = (hash*)malik( sizeof( hash ) );
  h->size = size;
  h->num_entries=0;
  h->entries = (hashentry**)malloc( size * sizeof(hashentry*) );
  memset( h->entries, 0, size * sizeof(hashentry*) );
  return h;
}

static unsigned int hashcode_string( char *s )
{
  unsigned int hc = 0;
  A(s);
  while (*s) {
    hc ^= *s;
    hc = (hc>>31) | ((hc&0x7fff)<<1);
    s++; 
  }

  return hc;
}

static unsigned int hashcode( dexp d )
{
  int i;
  unsigned int hc=0;

  DCK(d);
  switch( d->type ) {
    case dexp_char:
      hc = (unsigned int)d->v.char_v;
      break;
    case dexp_int:
      hc = (unsigned int)d->v.int_v;
      break;
    case dexp_float:
      hc = *((unsigned int*)(&d->v.float_v));
      break;
    case dexp_double:
      hc = *((unsigned int*)(&d->v.double_v));
      break;
    case dexp_string:
      hc = hashcode_string( d->v.string_v );
      break;
    case dexp_cons:
      //hc = (unsigned int)d;
      hc = hashcode_string( CONSCTORS( d ) );
      for (i=0; i<CONSCOUNT(d); ++i) {
        hc ^= hashcode( CONSELEM( d, i ) );
      }
      break;
    default:
      err(( "Bad dexp type %d\n", d->type ));
      break;
  }

  return hc;
}

void find_entry_and_prev( hash *h, unsigned int hc, dexp key,
  hashentry **entry, hashentry **prev_entry )
{
  hashentry *here, *prev;
  A(h);
  DCK(key);
  A(hc>=0 && hc<h->size);

  *entry = 0;
  *prev_entry = 0;

  prev = 0;
  here = h->entries[hc];
  while (here) {
    A(here->key);
    A(here->value);
    if (EQUAL( here->key, key )) {
      *entry = here;
      *prev_entry = prev;
    }
    prev = here;
    here = here->next;
  }
}

static hashentry *find_entry( hash *h, unsigned int hc, dexp key )
{
  hashentry *here;
  A(h);
  DCK(key);
  A(hc>=0 && hc<h->size);

  here = h->entries[hc];
  while (here) {
    A(here->key);
    A(here->value);
    if (EQUAL( here->key, key )) {
      return here;
    }
    here = here->next;
  }
  return 0;
}

static void copy_into( hash *dest, hash *src )
{
  FORHASH(src,k,v) {
    hashput( dest, k, v );
  }
}

static void resize( hash *h, int new_size )
{
  hash *nu = makehash( new_size );
//printf( "Resizing %p %d -> %d\n", h, h->size, new_size );
  copy_into( nu, h );
  *h = *nu;
}

void hashput( hash *h, dexp key, dexp value )
{
  unsigned int hc;

  DCK(key);
  DCK(value);

  hc = hashcode( key ) % h->size;
  A(hc>=0 && hc<h->size);
  hashentry *he = find_entry( h, hc, key );
  if (he==0) {
    he = (hashentry*)malik( sizeof( hashentry ) );
    he->key = key;
    he->value = value;
    he->next = h->entries[hc];
    h->entries[hc] = he;
    h->num_entries++;
  } else {
    he->value = value;
  }

  // Resize if table too small.
  if (h->num_entries >= h->size) {
    resize( h, h->size*2 );
  }
}

dexp hashget( hash *h, dexp key )
{
  int hc;
  hashentry *he;

  DCK(key);

  hc = hashcode( key ) % h->size;
  A(hc>=0 && hc<h->size);
  he = find_entry( h, hc, key );
  A((he?(EQUAL(he->key,key)):1));
  return he ? he->value : 0;
}

void hashdel( hash *h, dexp key )
{
  int hc;
  hashentry *he, *hprev;

  DCK(key);

  hc = hashcode( key ) % h->size;
  A(hc>=0 && hc<h->size);
  find_entry_and_prev( h, hc, key, &he, &hprev );
  A((he?(EQUAL(he->key,key)):1));

  if (hprev) {
    // Point parent to removee's child.
    hprev->next = he->next;
  } else {
    // Point table to removee's child.
    h->entries[hc] = he->next;
  }

  h->num_entries--;
}

void hash_init_iter( hashiter *hi, hash *h )
{
  A(hi);
  A(h);
  A(h->size>0);

  hi->h = h;
  hi->index = 0;
  hi->cursor = h->entries[0];
}

int hash_iter_next( hashiter *hi, dexp *key, dexp *value )
{
  A(hi);
  A(key);
  A(value);
  A(hi->h);
  A(hi->index>=0 && hi->index<=hi->h->size);

  while (hi->cursor == 0 && hi->index < hi->h->size) {
    hi->cursor = hi->h->entries[++hi->index];
  }

  if (hi->cursor!=0 && hi->index < hi->h->size) {
    *key = hi->cursor->key;
    *value = hi->cursor->value;

    hi->cursor = hi->cursor->next;

    return 1;
  } else {
    return 0;
  }
}

void hash_dump( hash *h )
{
  int i;
  spew(( "======== hash dump =========\n" ));
  for (i=0; i<h->size; ++i) {
    hashentry *he = h->entries[i];
    spew(( "at %d\n", i ));
    while (he) {
      spew(( "  [hashcode %x]\n", hashcode( he->key ) ));
      spew(( "    key " ));
      sldspew( he->key );
      spew(( "\n" ));
      spew(( "    value " ));
      sldspew( he->value );
      spew(( "\n" ));
      he = he->next;
    }
  }
  spew(( "........ hash dump .........\n" ));
}
