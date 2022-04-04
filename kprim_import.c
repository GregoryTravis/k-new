// $Id: kprim_import.c,v 1.1 2002/09/06 20:31:55 Administrator Exp $

#include "mem.h"

#include "kexec.h"
#include "kprim_import.h"

#define BUFSIZE 2048
static char buf[BUFSIZE];

DEFPRIM(import)
{
  int n;
  sexp file;
  char *filename;
  A(arglist);

  file = car( arglist );
  filename = SEXP_GET_STRING( file );

  printf( "IMPORT %s\n", filename );

  n = snprintf( buf, BUFSIZE, "%s.k", filename );

  if (n==-1) {
    err(( "Can't import %s, name too long.\n", filename ));
  }

  k_exec_file( strdoop( buf ) );

  return nil;
}
