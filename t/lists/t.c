// $Id: t.c,v 1.1 2004/08/06 14:14:30 greg Exp $

#include <stdio.h>
#include "../../dexp.h"
#include "../../hash.h"

int main( void )
{
  dexp d = mklist( mkint( 1 ), mkint( 2 ), mkint( 3 ) );
  dspew( d );

  // string of as
  dexp as =
    mkcons( "Term",
      mksymbol( "As" ),
      mkcons( "Cons",
        // First option: 'a'
        mkcons( "Cons",
          mkchar( 'a' ),
          mkcons( "Nil" ) ),
        // Second option: 'a' As
        mkcons( "Cons",
          mkcons( "Cons",
            mkchar( 'a' ),
            mkcons( "Cons",
              mksymbol( "As" ),
              mkcons( "Nil" ) ) ),
          mkcons( "Nil" ) ) ) );
  dspew( as );

  dexp as2 =
    mkcons( "Term",
      mksymbol( "As" ),
      mklist(
        mklist( mkchar( 'a' ) ),
        mklist( mkchar( 'a' ), mksymbol( "As" ) ) ) );

  dspew( as2 );

  printf( "EQUAL %d\n", EQUAL(as,as2) );

  return 0;
}
