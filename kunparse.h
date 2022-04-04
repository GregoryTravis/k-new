// $Id: kunparse.h,v 1.2 2002/08/22 20:55:09 Administrator Exp $

#ifndef _kunparse_h_
#define _kunparse_h_

#include <stdio.h>

#include "sexp.h"

void k_unparse( FILE *outstream, sexp sem );
void k_unparse_file( char *filename, sexp sem );

#endif /* _kunparse_h_ */
