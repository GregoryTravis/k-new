// $Id: fstrm.c,v 1.1 2002/09/03 19:42:20 Administrator Exp $

#include "a.h"
#include "fstrm.h"
#include "mem.h"

static void ofstrm_write( void *stuff, void *data, int length )
{
  int n;
  ofstrm *ofst = (ofstrm*)stuff;

  A(ofst);
  A(ofst->stream);

  n = fwrite( data, 1, length, ofst->stream );

  A(n==length);
}

static void ofstrm_close( void *stuff )
{
  ofstrm *ofst = (ofstrm*)stuff;

  A(ofst);
  A(ofst->stream);

  fclose( ofst->stream );

  ofst->stream = 0;
}

ostrm *ofstrm_create( char *filename )
{
  ofstrm *ofst;

  ofst = NEW(ofstrm);

  ofst->stream = fopen( filename, "w" );
  if (ofst==0) {
    err(( "Can't open %s\n", filename ));
  }

  return ostrm_create( ofst, &ofstrm_write, &ofstrm_close );
}

ostrm *ofstrm_create_from_stream( FILE *stream )
{
  ofstrm *ofst;

  ofst = NEW(ofstrm);

  ofst->stream = stream;

  return ostrm_create( ofst, &ofstrm_write, &ofstrm_close );
}
