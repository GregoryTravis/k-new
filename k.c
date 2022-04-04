// $Id: k.c,v 1.5 2002/09/05 22:03:51 Administrator Exp $

#include <stdio.h>
#include "keval.h"
#include "kexec.h"
#include "kinit.h"
#include "ksym.h"

int main( int argc, char *argv[] )
{
  int a;

  k_init();

  for (a=1; a<argc; ++a) {
    int ret;
    fprintf( stderr, "Running %s\n", argv[a] );

    k_exec_file( argv[a] );
  }

  ksym_dump_reasons( "k.reasons.out" );

  return 0;
}
