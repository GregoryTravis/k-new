// $Id: kprim_list.c,v 1.1 2002/09/03 20:24:02 Administrator Exp $

#include "sexp.h"

#include "kerr.h"
#include "kprim_list.h"

DEFPRIM(cons)
{
  A(arglist);

  if (length( arglist ) != 2) {
    kerr( "Wrong number of args for cons!" );
    KERRPUNTV(nil);
    return nil;
  } else {
    sexp a = car( arglist );
    sexp d = cadr( arglist );
    return cons( a, d );
  }
}

DEFPRIM(car)
{
  sexp a, d;

  A(arglist);

  if (length( arglist ) != 1) {
    kerr( "Wrong number of args for car!" );
    KERRPUNTV(nil);
    return nil;
  } else {
    sexp p = car( arglist );
    return car( p );
  }
}

DEFPRIM(cdr)
{
  sexp a, d;

  A(arglist);

  if (length( arglist ) != 1) {
    kerr( "Wrong number of args for cdr!" );
    KERRPUNTV(nil);
    return nil;
  } else {
    sexp p = car( arglist );
    return cdr( p );
  }
}
