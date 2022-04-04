// $Id: kerr.c,v 1.5 2002/10/22 20:33:41 Administrator Exp $

#include <stdarg.h>
#include <stdio.h>

#include "mem.h"
#include "spew.h"

#include "kerr.h"

int k_error = 0;

#define ERROR_BUF_SIZE 4096
static char error_buffer[ERROR_BUF_SIZE];

static sexp errors = CONST_NIL;

static void vkerr( sexp where, char *f, va_list va );

void kerr( char *f, ... )
{
  va_list va;

  k_error = 1;

  va_start(va,f);
  vkerr( nil, f, va );
  va_end(va);
}

void kerrw( sexp where, char *f, ... )
{
  va_list va;

  k_error = 1;

  va_start(va,f);
  vkerr( where, f, va );
  va_end(va);
}

static void vkerr( sexp where, char *f, va_list va )
{
  int written;
  char *errstring;

  /* the -1, +1 stuff is cuz vsnprintf doesn't count the trailing 0 */
  written = vsnprintf( error_buffer, ERROR_BUF_SIZE-1, f, va );
  if (written==-1) {
    errstring = "[Error message too long]";
  } else {
    errstring = strdoop( error_buffer );
  }

  errors = sexp_build( "(((message %)(where %)) . %)",
    SEXP_MKSTRING( errstring ),
    where,
    errors );
}

static void show_where( FILE *file, sexp where )
{
  sexp locinfo = SEXP_PROPERTIES( where );
  sexp filename_s, start_line_s, end_line_s, start_char_s, end_char_s, start_gchar_s, end_gchar_s;

  if (locinfo == nil) {
    fprintf( file, "(No location info): " );
  } else if (locinfo != 0 &&
      sexp_scan( locinfo, "((file %)(line % %) (char % %) (gchar % %))",
        &filename_s,
        &start_line_s, &end_line_s,
        &start_char_s, &end_char_s,
        &start_gchar_s, &end_gchar_s )) {

    char *filename = SEXP_GET_STRING( filename_s );
    int start_line = SEXP_GET_INTEGER( start_line_s );
    int end_line = SEXP_GET_INTEGER( end_line_s );
    int start_char = SEXP_GET_INTEGER( start_char_s );
    int end_char = SEXP_GET_INTEGER( end_char_s );
    int start_gchar = SEXP_GET_INTEGER( start_gchar_s );
    int end_gchar = SEXP_GET_INTEGER( end_gchar_s );

    fprintf( file, "%s:", filename );

    if (start_line != end_line) {
      fprintf( file, " lines %d-%d", start_line, end_line );
    } else {
      fprintf( file, " line %d", start_line );
    }

    if (start_char != end_char) {
      fprintf( file, ", chars %d-%d", start_char, end_char );
    } else {
      fprintf( file, ", char %d", start_char );
    }

    fprintf( file, ": " );

  } else {
    fprintf( file, "Bad where info: %d %d\n", where, locinfo );
    sexp_dump_stream( file, where );
  }
}

void k_err_dump( FILE *file )
{
  sexp e = errors;

  fprintf( file, "Errors:\n" );

  while (e != nil) {
    sexp s, ss, sss;

    if (sexp_scan( e, "(((message %)(where %)) . %)", &s, &ss, &sss )) {
      show_where( file, ss );
      fprintf( file, "%s.\n", SEXP_GET_STRING( s ) );
    } else {
      fprintf( file, "Badly formatted error list: " );
      SD(e);
      break;
    }

    e = cdr( e );
  }

  fflush( stderr );
}

void k_err_reset( void )
{
  errors = nil;
  k_error = 0;
}

int k_err_deal( void )
{
  int ret = 0;
  if (k_error) {
    ret = 1;
    k_err_dump( stderr );
    k_err_reset();
  }

  return ret;
}
