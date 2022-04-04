// $Id: t.c,v 1.1 2004/08/06 14:14:30 greg Exp $

#define ANOLINE

#include <stdio.h>
#include "../../dexp.h"
#include "../../hash.h"

int main( void )
{
  dexp c = K(Joe,C(a),C(b),C(c));
  dspew( c );
  dspew( gK(c,0) );
  dspew( gK(c,1) );
  dspew( gK(c,2) );
  dspew( gK(c,3) );
  return 0;
}
