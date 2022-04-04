// $Id: dspew.h,v 1.4 2005/02/28 14:52:44 greg Exp $

#ifndef _dspew_h_
#define _dspew_h_

#include "dexp.h"

void dspew_indent( dexp d, int indent );
void dspew( dexp d );
void sldspew( dexp d );
void dspew_file( dexp d, char *filname );
void ndspew( dexp d );
void lspew( char *s, dexp e );
void compspew( char *s, dexp e0, dexp e1 );

#endif /* _dspew_h_ */
