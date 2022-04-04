// $Id: ksym.h,v 1.3 2002/09/05 22:03:53 Administrator Exp $

#ifndef _ksym_h_
#define _ksym_h_

#include "sexp.h"

sexp ksym_new_sym( void );

void ksym_set_reason( sexp symbol, char *text, sexp info );
void ksym_dump_reasons( char *filename );

#endif /* _ksym_h_ */
