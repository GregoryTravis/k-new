// $Id: strm.h,v 1.1 2002/09/03 19:42:22 Administrator Exp $

#ifndef _strm_h_
#define _strm_h_

typedef struct ostrm {
  void *stuff;
  void (*write)( void *stuff, void *data, int length );
  void (*close)( void *stuff );
} ostrm ;

ostrm *ostrm_create( void *data,
  void (*write)( void *stuff, void *data, int length ),
  void (*close)( void *stuff ) );
int stprintf( ostrm *ost, char *format, ... );
void stputc( int c, ostrm *ost );
void ostrm_close( ostrm *ost );
void *ostrm_get_stuff( ostrm *ost );

#endif /* _strm_h_ */
