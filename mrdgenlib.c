/* $Id: mrdgenlib.c,v 1.1 2004/08/06 14:14:29 greg Exp $ */

#include <stdio.h>
#include "mrdgenlib.h"

static int debug = 0;

static int serial=0;
static int indent;

static void pindent( void )
{
  int i;
  for (i=0; i<indent; ++i) {
    putchar( ' ' );
  }
}

dexp mrdgen_call( dexp *memos, int funnum, dexp (*fun)( int ),
  char *buf, int bufsize, int pos, int debug )
{
  int memopos = (bufsize+1) * funnum + pos;
  int callno = serial++;
  dexp ans;

  if (debug) {
    pindent();
    printf( "-- [%d] e_%d( %d ) at \"%.20s%s\"\n", callno, funnum,
      pos, buf+pos, ((bufsize-pos)>20 ? "..." : "") );
    indent++;
  }

  if (memos[memopos]) {
    ans = memos[memopos];
  } else {
    ans = (*fun)( pos );
    memos[memopos] = ans;
  }

//printf( "-- %d %d %d\n", funnum, pos, memopos );
//dspew( ans );

  if (debug) {
    indent--;
    pindent();
    printf( ".. [%d] %s\n", callno, CONSCTORS(ans) );
  }

  return ans;
}

dexp mrdgen_parse_from_file( dexp(*fun)( char *, int ), char *filename )
{
  FILE *fp;
  int len, r;
  char *buf;
  dexp d;
  fp = fopen( filename, "r" );
  A(fp);
  fseek( fp, 0, SEEK_END );
  len = ftell( fp );
  fseek( fp, 0, SEEK_SET ); 
  buf = malik( len );
  r = fread( buf, 1, len, fp );
  A(r==len);
  d = (*fun)( buf, len );
  fri( buf );
  return d;
}
