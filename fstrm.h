// $Id: fstrm.h,v 1.1 2002/09/03 19:42:20 Administrator Exp $

#ifndef _fstrm_h_
#define _fstrm_h_

#include <stdio.h>

#include "strm.h"

typedef struct ofstrm {
  FILE *stream;
} ofstrm ;

ostrm *ofstrm_create( char *filename );
ostrm *ofstrm_create_from_stream( FILE *stream );

#endif /* _fstrm_h_ */
