// $Id: pt.h,v 1.3 2005/02/08 22:30:17 greg Exp $

#ifndef _pt_h_
#define _pt_h_

#include "dexp.h"

dexp pt_parse( dexp input );
dexp pt_parse_file( char *filename );
dexp pt_clean( dexp parsed );
dexp pt_postprocess( dexp tree );
void pt_self_host_test( void );
void pt_show( int onp );
dexp pt_get_bootstrap_grammar( void );

#endif /* _pt_h_ */
