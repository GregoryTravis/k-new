// $Id: kfile.c,v 1.6 2002/10/22 19:16:49 Administrator Exp $

#include "a.h"
#include "mem.h"

#include "kerr.h"
#include "kp.h"
#include "kfile.h"

sexp k_read_script( char *filename )
{
  FILE *infile;
  sexp parse;

  infile = fopen( filename, "r" );

  if (infile==NULL) {
    kerr( "No such file %s", filename );
  }

  if (!KERR) {
    parse = kp_parse( filename, infile );

    if (parse==nil) {
      kerr( "Parse error in %s\n", filename );
    }
  }

  fclose(infile);

  KERRPUNTV(nil);

  return parse;
}
