// $Id: kprim_boolean.h,v 1.1 2002/09/20 21:02:41 Administrator Exp $

#ifndef _kprim_boolean_h_
#define _kprim_boolean_h_

#include "sexp.h"

#define DECLBOOLEANOP(op,_name) \
  sexp boolop_##_name( sexp arglist )

#define DEFBOOLEANOP(_op,_name)                       \
sexp boolop_##_name( sexp arglist )                   \
{                                                     \
  sexp a, b;                                          \
  int at, bt;                                         \
                                                      \
  if (length( arglist ) != 2) {                       \
    sexp_dump( arglist );                             \
    kerr( "Wrong number of args for something" );     \
  }                                                   \
  KERRPUNTV(nil);                                     \
                                                      \
  a = car( arglist );                                 \
  b = cadr( arglist );                                \
                                                      \
  A(SEXP_OK(a));                                      \
  A(SEXP_OK(b));                                      \
                                                      \
  at = SEXP_TYPE( a );                                \
  bt = SEXP_TYPE( b );                                \
                                                      \
  if (at != SEXP_BOOLEAN || bt != SEXP_BOOLEAN) {     \
    kerr( "Bad argument types for something" );       \
  } else {                                            \
    int ab = SEXP_GET_BOOLEAN( a );                   \
    int bb = SEXP_GET_BOOLEAN( b );                   \
    int vb;                                           \
    sexp val;                                         \
                                                      \
    vb = ab _op bb;                                   \
    val = SEXP_MKBOOLEAN( vb );                       \
                                                      \
    return val;                                       \
  }                                                   \
                                                      \
  KERRPUNTV(nil);                                     \
  return nil;                                         \
}

DECLBOOLEANOP(&&,andand);
DECLBOOLEANOP(||,oror);

#endif /* _kprim_boolean_h_ */
