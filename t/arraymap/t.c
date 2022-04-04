// $Id: t.c,v 1.2 2005/02/18 20:56:24 greg Exp $

#include <stdio.h>
#include "../../dexp.h"
#include "../../hash.h"

int main( void )
{
  dexp array = mkarray( 4 );
  pA(array,0,mkint( 2 ));
  pA(array,1,L(I(50),I(2),C(h)));
  pA(array,2,M(I(50),S(fifty),C(h),ST(aitch),ST(jae),S(j)));
  pA(array,3,K(Joe,I(1),C(g)));
  dspew( array );

  dspew( gM(gA(array,2),I(50)) );

  pM(gA(array,2),I(50),S(FIFTY));
  dspew( array );

  pA(array,0,I(20));
  dspew( array );

  dspew( array );
  dM(gA(array,2),I(50));
  dspew( array );

  return 0;
}
