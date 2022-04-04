/* $Id: match.c,v 1.3 2005/02/18 22:32:41 greg Exp $ */

#include <stdio.h>
#include <string.h>
#include "match.h"

// Returns map of bindings.
dexp match_match( dexp pattern, dexp matchee )
{
  int i;
  dexp ret;

  if (CT(pattern,_)) {
    return M(gK(pattern,0),matchee);
  } else if (ISCONS(pattern) && ISCONS(matchee)) {
    if (CONSCOUNT(pattern) != CONSCOUNT(matchee)) {
      return 0;
    }
    if (strcmp( pattern->v.cons_v.ctor, matchee->v.cons_v.ctor )) {
      return 0;
    }
    ret = EMAP();
    for (i=0; i<CONSCOUNT(pattern); ++i) {
      dexp ret2 = match_match( CONSELEM(pattern,i), CONSELEM(matchee,i) );
      if (!ret2) {
        return 0;
      }
      ret = dexp_append( ret, ret2 );
    }
    return ret;
  } else if (ISCONS(pattern) != ISCONS(matchee)) {
    return 0;
  } else {
    spew(( "Bad pattern.\n" ));
    printf( "  Pattern:\n" );
    dspew_indent( pattern, 4 );
    printf( "  Matchee:\n" );
    dspew_indent( matchee, 4 );
    err(( "" ));
  }
  A(0);
  return Nil;
}

#if MATCH_DEBUG
dexp match_match_trace( dexp pattern, dexp matchee )
{
  dexp ret = match_match( pattern, matchee );
  printf( "Match %s:\n", ret ? "success" : "failure" );
  printf( "  pattern:\n" );
  dspew_indent( pattern, 4 );
  printf( "  matchee:\n" );
  dspew_indent( matchee, 4 );
  return ret;
}
#endif

dexp match_env_lookup( dexp env, dexp s )
{
  A(ISLIST(env));

  while (!EQUAL(env,Nil)) {
    dexp row = CAR(env);
    dexp value = gM(row,s);
    if (value) {
      return value;
    }
    
    env = CDR(env);
  }
  err(( "No such match variable %s", SYMSTRING(s) ));
  A(0);
  return Nil;
}
