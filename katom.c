// $Id: katom.c,v 1.2 2002/08/21 16:03:50 Administrator Exp $

#include "shav.h"

#include "katom.h"

static shav *atoms;

static int initted = 0;

static void katom_init()
{
  if (initted)
    return;

  atoms = make_shav_hash();

  initted = 1;
}

kvalue_atom *katom_get_atom( char *name )
{
  kvalue val;

  katom_init();

  FORHASH(atoms,aname,avalue,{
    if (!strcmp( aname, name )) {
      return (kvalue_atom*)get_obj( avalue );
    }
  });

  return 0;
}

void katom_put_atom( char *name, kvalue_atom *atom )
{
  put_hash( atoms, name, make_shav_obj( atom ) );
}
