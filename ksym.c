// $Id: ksym.c,v 1.3 2002/09/05 22:03:53 Administrator Exp $

#include "mem.h"
#include "spew.h"

#include "ksym.h"
#include "sexp.h"

static int unique_serial;

static char *prefix = "__k_sym_";
static char buf[40];

static sexp reasons = 0;

sexp ksym_new_sym( void )
{
  if (unique_serial>9999999) {
    err(( "Can't generate any more syms." ));
  }

  sprintf( buf, "%s%d", prefix, unique_serial );
  unique_serial++;
  return mksym( strdoop( buf ) );
}

void ksym_set_reason( sexp symbol, char *text, sexp info )
{
  if (reasons==0)
    reasons = nil;

  reasons = cons( L3( symbol, SEXP_MKSTRING( text ), info ), reasons );
}

void ksym_dump_reasons( char *filename )
{
  sexp_dump_file( filename, reasons );
}
