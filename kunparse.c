// $Id: kunparse.c,v 1.4 2002/08/22 20:55:09 Administrator Exp $

#include "spew.h"
#include "sexp.h"

#include "kmisc.h"
#include "kunparse.h"

#define INDENT_STEP (2)

void k_unparse( FILE *outstream, sexp sem )
{
  fprintf( outstream, "Unparse: unimplemented!\n" );
}

void k_unparse_file( char *filename, sexp sem )
{
  FILE *file = fopen( filename, "w" );
  if (!file) {
    err(( "Can't write %s\n", filename ));
  }
  k_unparse( file, sem );
  fclose( file );
}

