// $Id: t.c,v 1.1 2004/08/06 14:14:30 greg Exp $

#define ANOLINE

#include <stdio.h>
#include "../../dexp.h"
#include "../../hash.h"

int main( void )
{
  dexp array = AR(3);
  pA(array,0,I(0));
  pA(array,1,I(1));
  pA(array,2,I(2));
  dspew( array );
  pA(array,12,I(12));
  return 0;
}
