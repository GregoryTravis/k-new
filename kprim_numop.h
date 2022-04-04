// $Id: kprim_numop.h,v 1.2 2002/09/19 17:51:49 Administrator Exp $

#ifndef _kprim_numop_h_
#define _kprim_numop_h_

#include "sexp.h"

#include "kerr.h"

#define DECLNUMOPWRAPPER(name) \
  sexp numop_##name( sexp arglist );

#define DECLCONDOPWRAPPER(name) \
  sexp condop_##name( sexp arglist );

DECLNUMOPWRAPPER(plus);
DECLNUMOPWRAPPER(minus);
DECLNUMOPWRAPPER(times);
DECLNUMOPWRAPPER(divided);

DECLCONDOPWRAPPER(dequals);
DECLCONDOPWRAPPER(dnequals);
DECLCONDOPWRAPPER(lt);
DECLCONDOPWRAPPER(gt);
DECLCONDOPWRAPPER(lte);
DECLCONDOPWRAPPER(gte);

#endif /* _kprim_numop_h_ */
