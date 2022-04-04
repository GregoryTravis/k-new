/* $Id: mem.c,v 1.2 2002/09/11 20:01:49 Administrator Exp $ */

#include <stdlib.h>
#include <string.h>
#include "a.h"
#include "gc.h"
#include "mem.h"
#include "spew.h"

#ifdef MEM_USE_GC

void *malik_last( int size )
{
  return GC_malloc( size );
}

void *realik_last( void *mem, int size )
{
  return GC_realloc( mem, size );
}

void fri_last( void *mem )
{
  /* mwahahahahahaha */
}

#else

void *malik_last( int size )
{
  return malloc( size );
}

void *realik_last( void *mem, int size )
{
  return realloc( mem, size );
}

void fri_last( void *mem )
{
  free( mem );
}

#endif /* MEM_USE_GC */

void *malik_actual( char *file, int line, int size )
{
  void *mem;

  mem = malik_last( size );

  spew(( smem, "malik %x size %d file %s line %d\n",
    mem, size, file, line ));
  if (mem==0) err(( "malik: Out of memory allocating %d\n", size ));

  return mem;
}

/* This might not work right if we turn freeing off! Because it
   might call free. */
void *realik_actual( char *file, int line, void *mem, int size )
{
  void *rmem;

  rmem = realik_last( mem, size );

  spew(( smem, "realik %x size %d was %x file %s line %d\n",
    rmem, size, mem, file, line ));
  if (rmem==0) err(( "realik: Out of memory allocating %d\n", size ));

  return rmem;
}

void fri_actual( char *file, int line, void *mem )
{
  spew(( smem, "fri %x file %s line %d\n",
    mem, file, line ));

  fri_last( mem );
}

void memkapi( void *dest, void *src, int len )
{
  memcpy( dest, src, len );
}

void strkapi( char *dest, char *src )
{
  strcpy( dest, src );
}

void *memfill( void *dest, int c, int n )
{
  return memset( dest, c, n );
}

char *strdoop( char *s )
{
  char *ss = (char*)malik( strlen( s ) );
  strcpy( ss, s );

  spew(( smem, "strdup 0x%x <- 0x%x\n", ss, s ));
  return ss;
}

void *cmalik( int size )
{
  void *mem = malik( size );
  memfill( mem, 0, size );
  return mem;
}

char *strkat( char *s0, char *s1 )
{
  int len0 = strlen( s0 );
  int len1 = strlen( s1 );

  char *c = malik( len0+len1+1 );
  strkapi( c, s0 );
  strkapi( c+len0, s1 );

  return c;
}
