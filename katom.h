// $Id: katom.h,v 1.2 2002/08/21 16:03:50 Administrator Exp $

#ifndef _katom_h_
#define _katom_h_

#include "kvalue.h"

kvalue_atom *katom_get_atom( char *name );
void katom_put_atom( char *name, kvalue_atom *atom );

#endif /* _katom_h_ */
