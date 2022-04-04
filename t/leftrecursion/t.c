// $Id: t.c,v 1.2 2005/02/17 17:26:29 greg Exp $

#include <stdio.h>
#include <stdio.h>
#include "../../io.h"
#include "../../mrd.h"
#include "../../pt.h"

int main( void )
{
  char *grammar_file="t/leftrecursion/lr.k",
       *input_file="t/leftrecursion/ab.txt";

  dexp grammar = pt_parse_file( grammar_file );
  grammar = mrd_cook( grammar );
  dexp input = io_read_file( input_file );
  dexp parsed = mrd_parse( grammar, S(aye), input );

  dspew( parsed );
  return 0;
}
