// $Id: k.c,v 1.3 2005/02/18 20:27:08 greg Exp $

#include <stdio.h>
#include "mrdgenlib.h"
#include "pt.h"

int main( void )
{
  dexp in = pt_parse_file( "input.k" );
  dspew( in );
  return 0;
}
