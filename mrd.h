/* $Id: mrd.h,v 1.3 2004/08/09 19:01:11 greg Exp $ */

#ifndef _mrd_h_
#define _mrd_h_

#include "dexp.h"

dexp mrd_parse( dexp grammar, dexp top, dexp input );
dexp mrd_cook( dexp raw );
dexp mrd_merge( dexp a, dexp b );
void mrd_show( int onp );

#endif /* _mrd_h_ */
