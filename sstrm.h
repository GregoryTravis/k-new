// $Id: sstrm.h,v 1.1 2002/09/03 19:42:22 Administrator Exp $

#ifndef _sstrm_h_
#define _sstrm_h_

#include "growbuf.h"
#include "strm.h"

typedef struct osstrm {
  growbuf *gb;
} osstrm ;

ostrm *osstrm_create( void );
char *osstrm_get( ostrm *ost );

#endif /* _sstrm_h_ */
