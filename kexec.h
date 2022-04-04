// $Id: kexec.h,v 1.2 2002/09/11 20:04:23 Administrator Exp $

#ifndef _kexec_h_
#define _kexec_h_

#include "sexp.h"

sexp k_prepare_file( char *filename );
int k_exec_file( char *filename );

#endif /* _kexec_h_ */
