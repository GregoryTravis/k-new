/* $Id: ptgen.c,v 1.2 2004/08/09 19:01:11 greg Exp $ */

#include "pt.h"
#include "ptgen.h"
#include "grammar.h"

dexp ptgen_parse_file( char *filename )
{
  dexp raw = grammar_file( filename );

  CASE (raw) {
    match (K(Ok,_(tree))) {
      return pt_postprocess( pt_clean( V(tree) ) );
    } else match (K(Bad,_(why))) {
      return raw;
    }
  } ENDCASE;
  A(0);
  return Nil;
}
