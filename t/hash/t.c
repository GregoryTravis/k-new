// $Id: t.c,v 1.2 2005/02/18 20:56:24 greg Exp $

#include <stdio.h>
#include "../../dexp.h"
#include "../../hash.h"

int main( void )
{
  hash *h = makehash( 2 );

  hash_dump( h );

  hashput( h, mksymbol( "asdf" ), mkint( 10 ) );
  hash_dump( h );
  hashput( h, mksymbol( "asdfj" ), mkint( 12 ) );
  hash_dump( h );

  dspew( hashget( h, mksymbol( "asdf" ) ) );
  dspew( hashget( h, mksymbol( "asdfj" ) ) );

  hashput( h, mksymbol( "asdf" ), mkint( 100 ) );
  hash_dump( h );
  hashput( h, mksymbol( "asdfj" ), mkint( 120 ) );
  hash_dump( h );

  dspew( hashget( h, mksymbol( "asdf" ) ) );
  dspew( hashget( h, mksymbol( "asdfj" ) ) );

  hashdel( h, mksymbol( "asdf" ) );
  hash_dump( h );
  hashdel( h, mksymbol( "asdfj" ) );
  hash_dump( h );

  return 0;
}
