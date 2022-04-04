// $Id: t.c,v 1.1 2004/08/06 14:14:30 greg Exp $

#include <stdio.h>
#include "../../pt.h"
#include "../../ptgen.h" // for linkage

int main( void )
{
  dexp in = pt_parse_file( "grammar.k" );
  dexp gen_in = ptgen_parse_file( "grammar.k" );

  printf( "equal %d\n", EQUAL(in,gen_in) );
  return 0;
}
