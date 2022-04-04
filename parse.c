// $Id: parse.c,v 1.1 2005/01/28 20:31:09 greg Exp $

#include <stdio.h>
#include <stdio.h>
#include "io.h"
#include "mrd.h"
#include "pt.h"

int main( int argc, char *argv[] )
{
  char *grammar_file, *input_file;
  if (argc != 3) {
    err(( "Usage: %s grammar file\n", argv[0] ));
  }
  grammar_file = argv[1];
  input_file = argv[2];

  dexp grammar = pt_parse_file( grammar_file );
  grammar = mrd_cook( grammar );
  dexp input = io_read_file( input_file );
  dexp parsed = mrd_parse( grammar, S(aye), input );

//  dspew( grammar );

  dspew( parsed );
  return 0;
}
