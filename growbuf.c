// $Id: growbuf.c,v 1.3 2002/10/08 16:04:31 Administrator Exp $

#include <stdio.h>

#include "a.h"
#include "growbuf.h"

growbuf *gb_create( void )
{
  growbuf *gb;

  gb = NEW(growbuf);
  gb->mem = 0;
  gb->length = 0;
  gb->capacity = 0;

  return gb;
}

void gb_concat( growbuf *gb, void *mem, int howmuch )
{
  A(gb);

  if (gb->mem==0) {
    gb->mem = malik( howmuch );
    gb->capacity = howmuch;
  } else {
    int needed = gb->length + howmuch;
    if (gb->capacity < needed) {
      int newcap = gb->capacity * 2;
      if (newcap < needed)
        newcap = needed;
      gb->mem = realik( gb->mem, newcap );
      gb->capacity = newcap;
    }
  }

  memkapi( gb->mem+gb->length, mem, howmuch );
  gb->length += howmuch;
}

void gb_concat_string( growbuf *gb, char *string )
{
  gb_concat( gb, string, strlen( string ) );
}

void *gb_get( growbuf *gb )
{
  A(gb);
  return gb->mem;
}

int gb_get_size( growbuf *gb )
{
  A(gb);
  return gb->length;
}
