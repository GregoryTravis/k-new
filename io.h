/* $Id: io.h,v 1.1 2004/08/06 14:14:29 greg Exp $ */

#ifndef _io_h_
#define _io_h_

#include "dexp.h"

dexp io_read_file( char *filename );
void io_write_charlist( FILE *fp, dexp charlist, int start, int end );
void io_redirect_stdout( char *filename );
void io_restore_stdout( void );
void io_redirect_stdout_fp( FILE *fp );

#endif /* _io_h_ */
