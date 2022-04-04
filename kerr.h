// $Id: kerr.h,v 1.4 2002/10/22 19:16:49 Administrator Exp $

#ifndef _kerr_h_
#define _kerr_h_

#include <stdio.h>

#include "sexp.h"

extern int k_error;

void kerr( char *f, ... );
void kerrw( sexp where, char *f, ... );
void k_err_dump( FILE *file );
void k_err_reset( void );
int k_err_deal( void );

#define KERR (k_error)

#define KERRBREAK do { if (KERR) break; } while (0)
#define KERRPUNT do { if (KERR) return; } while (0)
#define KERRPUNTV(v) do { if (KERR) return (v); } while (0)

#endif /* _kerr_h_ */
