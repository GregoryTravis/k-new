/* $Id: a.h,v 1.4 2002/10/08 18:42:59 Administrator Exp $ */

#ifndef _a_h_
#define _a_h_

#include "spew.h"

typedef unsigned char bool;
typedef unsigned char uchar;

#define ASSERT

#define _A(expr) ((expr) ? 0 : \
  (err(( "Assert %s %d: %s\n", __FILE__, __LINE__, #expr )),0) )
#define _RA(expr,rept) \
  ( \
    (expr) ?  0 : \
      (warn(("Assert %s %d: %s: ", __FILE__, __LINE__, #expr )), \
      err(rept),0) \
  )

#ifdef ASSERT

#define A(expr) _A(expr)
#define RA(expr,rept) _RA(expr,rept)

#else

#define A(expr) 0
#define RA(expr,rept) 0

#endif

#define AA(expr) _A(expr)
#define RAA(expr,rept) _RA(expr,rept)

#define ML() printf( "MARK %s:%d\n", __FILE__, __LINE__ )

#endif /* _a_h_ */
