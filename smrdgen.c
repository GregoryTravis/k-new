// $Id: smrdgen.c,v 1.5 2005/02/18 22:32:41 greg Exp $

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dexp.h"
#include "mrd.h"
#include "mrdgen.h"
#include "pt.h"

static int verbose = 0;

int main( int argc, char *argv[] )
{
  int a, aa;
  char *pp;
  dexp grammar;
  char *top_symbol, *parser_name;
  char buf[4096];

  // Grab options
  a=1;
  aa=1;
  while (a<argc) {
    if (argv[a][0] == '-') {
      if (!strcmp( argv[a]+1, "v" )) {
        verbose = 1;
      } else {
        spew(( "Bad option: %s\n", argv[a] ));
        err(( "" ));
      }
      argv[aa] = argv[a];
    } else {
      argv[aa] = argv[a];
      aa++;
    }
    a++;
  }
  argc=aa;

  if (argc < 4) {
    fprintf( stderr,
      "Usage: %s parser-name top-symbol grammar-file [grammar-file...]\n",
      argv[0] );
    exit( 1 );
  }

  grammar = EMAP();

  parser_name = argv[1];
  top_symbol = argv[2];
  for (a=3; a<argc; ++a) {
    char *grammar_file = argv[a];
    dexp g;

    pp = strchr( grammar_file, '.' );
    if (pp) {
      *pp = 0;
    }

    sprintf( buf, "%s.k", grammar_file );
    if (verbose) { printf( "  Reading %s\n", buf ); }
    g = pt_parse_file( buf );
    g = mrd_cook( g );
    grammar = mrd_merge( grammar, g );
  }

  if (verbose) { printf( "  Generating code for '%s'", parser_name ); }
  mrdgen( grammar, mksymbol(top_symbol), parser_name );

  return 0;
}
