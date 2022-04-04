/* $Id: io.c,v 1.2 2005/02/17 17:27:10 greg Exp $ */

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include "io.h"

dexp io_read_file( char *filename )
{
  int size, ret, i;
  dexp bytes;

  FILE *fp = fopen( filename, "r" );
  RA(fp,("Can't open \"%s\"",filename));

  ret = fseek( fp, 0, SEEK_END );
  A(!ret);
  size = ftell( fp );
  A(size != -1);
  ret = fseek( fp, 0, SEEK_SET );
  A(!ret);

  bytes = mkarray( size );

  for (i=0; i<size; ++i) {
    int c = fgetc( fp );
    RA(c!=-1,("EOF at position %d\n", i));
    pA(bytes,i,mkchar(c));
  }

  fclose( fp );

  return bytes;
}

void io_write_charlist( FILE *fp, dexp charlist, int start, int end )
{
  int i;
  printf( "\"" );
  for (i=start; i<end; ++i) {
    putchar( gC( gA( charlist, i ) ) );
  }
  printf( "\"" );
}

static FILE *io_stdout_copy=0;
void io_redirect_stdout( char *filename )
{
  A(!io_stdout_copy);
  fflush( stdout );
  io_stdout_copy = fdopen( dup( fileno( stdout ) ), "w" );
  close( fileno( stdout ) );
  fopen( filename, "w" );
}

void io_redirect_stdout_fp( FILE *fp )
{
  A(!io_stdout_copy);
  fflush( stdout );
  fflush( fp );
  io_stdout_copy = fdopen( dup( fileno( stdout ) ), "w" );
  close( fileno( stdout ) );
  dup( fileno( fp ) );
}

void io_restore_stdout( void )
{
  A(io_stdout_copy!=0);
  fflush( stdout );
  close( fileno( stdout ) );
  dup( fileno( io_stdout_copy ) );
  fflush( stdout );
  io_stdout_copy = 0;
}
