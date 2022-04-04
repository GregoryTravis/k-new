// $Id: t.c,v 1.2 2005/02/01 21:05:49 greg Exp $

#define ANOLINE

#include <stdio.h>
#include <string.h>
#include "../../dexp.h"
#include "../../hash.h"
#include "../../match.h"

void blah( dexp d )
{
dspew( d );
  CASE (d) {
    match (K(Jer,K(Queen,_(t),_(u)),_(b))) {
      spew(( "0\n" ));
      dspew( K(Jer,V(t),V(u),V(b)) );
    } else match (K(Jer,_(a),_(b))) {
      spew(( "1\n" ));
      dspew( K(Jer,V(b),V(a)) );
    } else match( K(Joe,K(A,_(a)),_(b)) ) {
      spew(( "2\n" ));
      dspew( K(Jer,V(b),V(a)) );
    }
  } ENDCASE;
}

int main( void )
{
  blah( K(Jer,K(Queen,K(Lap,I(8)),I(9)),F(1.2)) );
  blah( K(Jer,K(Queen,K(Lip,I(8)),I(9),I(20)),F(1.2)) );
  blah( K(Joe,K(A,I(3)),C(4)) );
  blah( K(Vope,I(1)) );

  return 0;
}
