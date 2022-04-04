// $Id: t.c,v 1.1 2004/08/06 14:14:30 greg Exp $

#include <stdio.h>
#include "../../dexp.h"
#include "../../hash.h"

int main( void )
{
  dspew( mkchar( 'q' ) );
  dspew( mkint( 3 ) );
  dspew( mkfloat( 3.3 ) );
  dspew( mkdouble( 5.5 ) );
  dspew( mkstring( "glove" ) );
  dspew( mksymbol( "asdf" ) );
  printf( "%d\n", mksymbol( "asdf" ) == mksymbol( "asdf" ) );

  dspew( mkcons( "Foo", mkint( 20 ), mkfloat( 45.6 ),
           mkcons( "Blen", mkstring( "vain" ),
             mkcons( "Pigg", mkdouble( 4.5 ), mkchar( 'v' ),
               mksymbol( "adobe" ) ) ) ) );

  return 0;
}
