// $Id: growbuf.h,v 1.1 2002/09/03 19:42:21 Administrator Exp $

#ifndef _growbuf_h_
#define _growbuf_h_

#include "mem.h"

typedef struct growbuf {
  void *mem;
  int length;
  int capacity;
} growbuf ;

growbuf *gb_create( void );
void gb_concat( growbuf *gb, void *mem, int howmuch );
void gb_concat_string( growbuf *gb, char *string );
void *gb_get( growbuf *gb );
int gb_get_size( growbuf *gb );

#endif /* _growbuf_h_ */
