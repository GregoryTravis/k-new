// $Id: sstrm.c,v 1.1 2002/09/03 19:42:22 Administrator Exp $

#include "a.h"
#include "growbuf.h"
#include "mem.h"
#include "sstrm.h"

static void osstrm_write( void *stuff, void *data, int length )
{
  osstrm *osst = (osstrm*)stuff;

  A(osst);
  A(osst->gb);

  gb_concat( osst->gb, data, length );
}

static void osstrm_close( void *stuff )
{
  osstrm *osst = (osstrm*)stuff;

  A(osst);
  A(osst->gb);

  gb_concat( osst->gb, "\0", 1 );
}

ostrm *osstrm_create( void )
{
  ostrm *ost;
  osstrm *osst;

  osst = NEW(osstrm);

  osst->gb = gb_create();

  ost = ostrm_create( osst, &osstrm_write, &osstrm_close );

  return ost;
}

char *osstrm_get( ostrm *ost )
{
  osstrm *osst;

  A(ost);

  osst = ostrm_get_stuff( ost );
  A(osst);
  A(osst->gb);

  return gb_get( osst->gb );
}
