/* $Id: mrdgenlib.h,v 1.1 2004/08/06 14:14:29 greg Exp $ */

#ifndef _mrdgenlib_h_
#define _mrdgenlib_h_

#include "dexp.h"

#define call(funnum,pos) \
  mrdgen_call( memos, funnum, &e_##funnum, buf, bufsize, pos, MRDGEN_DEBUG )

dexp mrdgen_call( dexp *memos, int funnum, dexp (*fun)( int ),
  char *buf, int bufsize, int pos, int debug );
dexp mrdgen_parse_from_file( dexp(*fun)( char *, int ), char *filename );

#endif /* _mrdgenlib_h_ */
