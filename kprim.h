// $Id: kprim.h,v 1.3 2002/09/12 16:29:34 Administrator Exp $

#ifndef _kprim_h_
#define _kprim_h_

#include "sexp.h"

void kprim_add_prims( sexp env );

#define DEFPRIM(name) \
  sexp __prim_##name( sexp arglist )

#define DECLPRIM(name) \
  sexp __prim_##name( sexp arglist )

#define ADDPRIM(env,name) \
  kenv_global_put_env( env, mksym( #name ), SEXP_MKNATIVE( __prim_##name ) )

#endif /* _kprim_h_ */
