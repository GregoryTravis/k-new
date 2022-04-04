// $Id: t.c,v 1.1 2004/08/06 14:14:30 greg Exp $

#include <stdio.h>
#include "../../dexp.h"

int main( void )
{
  char buf[200];
  int i;
  int n = 8192;

  for (i=0; i<n; ++i) {
    sprintf( buf, "atom%d", i );
    mksymbol( buf );
  }

  for (i=0; i<n; ++i) {
    sprintf( buf, "atom%d", i );
//    printf( "%d", mksymbol( buf ) == mksymbol( buf ) );
    putchar( mksymbol( buf ) == mksymbol( buf ) ? '1' : '0' );
  }
  printf( "\n" );

  return 0;
}
