// $Id: strm.c,v 1.1 2002/09/03 19:42:22 Administrator Exp $

#include <stdarg.h>
#include <stdio.h>

#include "a.h"
#include "mem.h"
#include "strm.h"

#define ST_BUF_SIZE (64 * 1024)
static char stbuf[ST_BUF_SIZE];

ostrm *ostrm_create( void *stuff,
  void (*write)( void *stuff, void *data, int length ),
  void (*close)( void *stuff ) )
{
  ostrm *ost;

  ost = NEW(ostrm);

  ost->stuff = stuff;
  ost->write = write;
  ost->close = close;

  return ost;
}

int stprintf( ostrm *ost, char *format, ... )
{
  int n;
  va_list va;

  A(ost);
  A(ost->write);

  va_start( va, format );
  n = vsnprintf( stbuf, ST_BUF_SIZE, format, va );
  va_end( va );

  (*ost->write)( ost->stuff, stbuf, n );

  return n;
}

void stputc( int c, ostrm *ost )
{
  A(ost);
  A(ost->write);

  (*ost->write)( ost->stuff, &c, 1 );
}

void ostrm_close( ostrm *ost )
{
  A(ost);
  A(ost->close);

  (*ost->close)( ost->stuff );
}

void *ostrm_get_stuff( ostrm *ost )
{
  A(ost);

  return ost->stuff;
}
