/* $Id: match.h,v 1.4 2005/02/10 14:22:18 greg Exp $ */

#ifndef _match_h_
#define _match_h_

#include "dexp.h"
#include "dspew.h"

#define MATCH_DEBUG 0

#if MATCH_DEBUG
# define MATCH_MATCH match_match_trace
#else
# define MATCH_MATCH match_match
#endif

#define V(__var) match_env_lookup( __match_results, mksymbol(#__var) )

#define V_(__var)                                \
  ( RA(gM(__match_results,mksymbol(#__var)),            \
       ("No such match variable %s.", #__var)), \
    gM(__match_results,mksymbol(#__var)) )

#define CASE(d)         \
if (1) {\
    dexp __pip=0; \
    dexp __gug=__match_results, __match_results = __gug; \
    if (!__match_results) { __match_results = Nil; } \
    dexp __matchee = (d); \
    DCK((__matchee));

#define match(__pattern) \
    if ((__pip = MATCH_MATCH( (__pattern), __matchee )) ? \
        ((__match_results=CONS(__pip,__match_results)),1) : 0)

#define otherwise(__var) else match (_(__var))

#define ornot otherwise(__var) {}

#define ENDCASE                  \
    if (!__pip) {                \
      spew(( "Case error:\n" )); \
      spew(( "matchee: " ));     \
      dspew( __matchee );        \
      err(( "" ));               \
    } else {                     \
      __match_results = CDR( __match_results ); \
    } \
} else do {} while (0)


dexp match_match_trace( dexp pattern, dexp matchee );
dexp match_match( dexp pattern, dexp matchee );
dexp match_env_lookup( dexp env, dexp s );

#define _(_a) K(_,S(_a))

static dexp __match_results = 0;

#endif /* _match_h_ */
