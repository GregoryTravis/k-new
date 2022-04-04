// $Id: sexputil.c,v 1.1 2002/09/05 22:03:53 Administrator Exp $

#include "sexputil.h"

sexp cars( sexp lyst )
{
  if (SEXP_IS_NIL( lyst )) {
    return lyst;
  } else if (SEXP_IS_CONS( lyst )) {
    return cons( car( car( lyst ) ), cars( cdr( lyst ) ) );
  } else {
    err(( "Bad lyst for cars" ));
    return nil;
  }
}

sexp cadrs( sexp lyst )
{
  if (SEXP_IS_NIL( lyst )) {
    return lyst;
  } else if (SEXP_IS_CONS( lyst )) {
    return cons( cadr( car( lyst ) ), cadrs( cdr( lyst ) ) );
  } else {
    err(( "Bad lyst for cars" ));
    return nil;
  }
}
