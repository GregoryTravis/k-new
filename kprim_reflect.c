// $Id: kprim_reflect.c,v 1.1 2002/10/08 18:43:00 Administrator Exp $

#include "sexp.h"

#include "kerr.h"
#include "kprim_reflect.h"

DEFPRIM(closure_get_code)
{
  A(arglist);

  if (length( arglist ) != 1) {
    kerr( "Wrong number of args for closure_show_code" );
    KERRPUNTV(nil);
    return nil;
  } else {
    sexp closure = car( arglist );

    if (!SEXP_IS_CLOSURE( closure )) {
      kerr( "Error: not a closure" );
      KERRPUNTV(nil);
      return nil;
    } else {
      return SEXP_GET_CLOSURE_CODE( closure );
    }
  }
}
