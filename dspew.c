// $Id: dspew.c,v 1.8 2005/03/01 15:59:17 greg Exp $

#include <stdio.h>
#include <string.h>
#include "dspew.h"
#include "io.h"
#include "spew.h"

#define DSPEW_STREAM SPEW_STREAM

#define SPECIAL_CASED_PP 1

static void pindent( int indent )
{
  int i;
  for (i=0; i<indent; ++i) {
    fputc( ' ', DSPEW_STREAM );
  }
}

#define PRINTABLE(_c) \
  ((_c)>=' ' && (_c)<='~' && (_c)!='\\' && (_c)!='\"' && (_c)!='\\')

static char *printable_char( char c )
{
  static char buf[5];
  if (PRINTABLE(c)) {
    buf[0] = c;
    buf[1] = 0;
    return buf;
  } else {
    switch (c) {
      case '\n':
        return "\\n";
        break;
      case '\t':
        return "\\t";
        break;
      case '\'':
        return "\\\'";
        break;
      case '\"':
        return "\\\"";
        break;
      case '\\':
        return "\\\\";
        break;
      default:
        {
          int n = snprintf( buf, 5, "\\x%.2x", (int)c );
          A(n==4);
          return buf;
          break;
        }
    }
  }
}

static int escaped_length( char *s )
{
  int len = 0;
  while (*s) {
    char c = *s++;
    if (PRINTABLE( c )) {
      len++;
    }
  }
  return len;
}

static void escaped_string_print( FILE *stream, char *s )
{
  while (*s) {
    char c = *s++;
    fprintf( stream, "%s", printable_char( c ) );
  }
}

#define TARGET_WIDTH (70)
#define INDENTSZ (2)

#define WBUFLEN 64
static char wbuf[WBUFLEN];
static int width( dexp d )
{
  DCK(d);

  switch (d->type) {
    case dexp_char:
      return strlen( printable_char( gC(d) ) )+2;
      break;
    case dexp_int:
      return snprintf( wbuf, WBUFLEN, "%d", gI(d) );
      break;
    case dexp_float:
      return snprintf( wbuf, WBUFLEN, "%f", gF(d) );
      break;
    case dexp_double:
      return snprintf( wbuf, WBUFLEN, "%f", gD(d) );
      break;
    case dexp_string:
      return escaped_length( gST(d) );
      break;
    case dexp_array:
      {
        int i;
        int len = 4; // "[  ]"
        FORARRAY (d,de) {
          len++; // interstitial spaces
          len += width( de );
        }
        len--; // one fewer interstices
        return len;
      }
      break;
    case dexp_tuple:
      {
        int i;
        int len = 4; // "(  )"
        FORTUPLE (d,de) {
          len++; // interstitial spaces
          len += width( de );
        }
        len--; // one fewer interstices
        return len;
      }
      break;
    case dexp_map:
      {
        int len = 4; // "{  }";
        FORMAP (d,k,v) {
          len += 2; // interstitial ", "
          len += 4; // " => "
          len += width( k );
          len += width( v );
        }
        len -= 2; // one fewer interstices
        return len;
      }
      break;
    case dexp_cons:
      if (ISLIST(d)) {
        if (ISPAIR(d)) {
          return width( CAR(d) )+width( CDR(d) )+2; // ", "
        } else {
          return 2-2; // "()" - extra ", ";
        }
      } else if (ISSYMBOL(d)) {
        return strlen( SYMSTRING(d) )+1; // single quote
      } else {
        int len = strlen( CONSCTORS(d) );
        len += 4; // "(  )";
        FORCTOR (d,de) {
          len += width( de );
          len += 2; // ", "
        }
        len -= 2; // extra interstitial
        return len;
      }
      break;
    default:
      err(( "??" ));
      break;
  }
  err(( "nope" ));
  return 0;
}

// nl is '\n' or ' ', depending on whether you want everything on one
// line or not.
void dspew1( dexp d, int level, char nl )
{
  int hor;

  DCK(d);
  A(level>=0);

  int w = width( d );

  hor = w+level < TARGET_WIDTH;

  switch (d->type) {
    case dexp_char:
      fprintf( DSPEW_STREAM, "'%s'", printable_char( gC( d ) ) );
      break;
    case dexp_int:
      fprintf( DSPEW_STREAM, "%d", gI( d ) );
      break;
    case dexp_float:
      fprintf( DSPEW_STREAM, "%f", gF( d ) );
      break;
    case dexp_double:
      fprintf( DSPEW_STREAM, "%f", gD( d ) );
      break;
    case dexp_string:
      fputc( '\"', DSPEW_STREAM );
      escaped_string_print( DSPEW_STREAM, gST(d) );
      fputc( '\"', DSPEW_STREAM );
      break;
    case dexp_array:
      {
        fputc( '{', DSPEW_STREAM );
        if (hor) {
          if (ARRAYSIZE( d ) > 0) {
            fputc( ' ', DSPEW_STREAM );
          }
        } else {
          fputc( nl, DSPEW_STREAM );
          if (nl == '\n') { pindent( level+1*INDENTSZ ); }
        }
        FORARRAY (d,de) {
          dspew1( de, level+1, nl );
          if (deinx<ARRAYSIZE(d)-1) {
            if (hor) {
              fprintf( DSPEW_STREAM, ", " );
            } else {
              fputc( ',', DSPEW_STREAM );
              fputc( nl, DSPEW_STREAM );
              if (nl == '\n') { pindent( (level+1)*INDENTSZ ); }
            }
          }
        }
        if (hor) {
          if (ARRAYSIZE( d ) > 0) {
            fputc( ' ', DSPEW_STREAM );
          }
        } else {
          fputc( nl, DSPEW_STREAM );
          if (nl == '\n') { pindent( level*INDENTSZ ); }
        }
        fprintf( DSPEW_STREAM, "}" );
      }
      break;
    case dexp_tuple:
      {
        fputc( '(', DSPEW_STREAM );
        if (hor) {
          if (TUPLESIZE( d ) > 0) {
            fputc( ' ', DSPEW_STREAM );
          }
        } else {
          fputc( nl, DSPEW_STREAM );
          if (nl == '\n') { pindent( level+1*INDENTSZ ); }
        }
        FORTUPLE (d,de) {
          dspew1( de, level+1, nl );
          if (deinx<TUPLESIZE(d)-1) {
            if (hor) {
              fprintf( DSPEW_STREAM, ", " );
            } else {
              fputc( ',', DSPEW_STREAM );
              fputc( nl, DSPEW_STREAM );
              if (nl == '\n') { pindent( (level+1)*INDENTSZ ); }
            }
          }
        }
        if (hor) {
          if (TUPLESIZE( d ) > 0) {
            fputc( ' ', DSPEW_STREAM );
          }
        } else {
          fputc( nl, DSPEW_STREAM );
          if (nl == '\n') { pindent( level*INDENTSZ ); }
        }
        fprintf( DSPEW_STREAM, ")" );
      }
      break;
    case dexp_map:
      fputc( '{', DSPEW_STREAM );
      if (hor) {
        if (MAPSIZE( d ) > 0) {
          fputc( ' ', DSPEW_STREAM );
        }
      } else {
        fputc( nl, DSPEW_STREAM );
        if (nl == '\n') { pindent( (level+1)*INDENTSZ ); }
      }
      FORMAP (d,k,v) {
        dspew1( k, level+1, nl);
        if (hor) {
          fputc( ' ', DSPEW_STREAM );
        } else {
          fputc( nl, DSPEW_STREAM );
          if (nl == '\n') { pindent( (level+2)*INDENTSZ ); }
        }
        fprintf( DSPEW_STREAM, "=>" );
        if (hor) {
          fputc( ' ', DSPEW_STREAM );
        } else {
          fputc( nl, DSPEW_STREAM );
          if (nl == '\n') { pindent( (level+1)*INDENTSZ ); }
        }
        dspew1( v, level+1, nl );
        fputc( ',', DSPEW_STREAM );
        if (hor) {
          fputc( ' ', DSPEW_STREAM );
        } else {
          fputc( nl, DSPEW_STREAM );
          if (nl == '\n') { pindent( (level+1)*INDENTSZ ); }
        }
      }
      if (hor) {
        if (MAPSIZE( d ) > 0) {
          fputc( ' ', DSPEW_STREAM );
        }
      } else {
        fputc( nl, DSPEW_STREAM );
        if (nl == '\n') { pindent( level*INDENTSZ ); }
      }
      fputc( '}', DSPEW_STREAM );
      break;
    case dexp_cons:
      if (ISLIST( d )) {
        dexp here;
        fprintf( DSPEW_STREAM, "[" );
        if (hor) {
        } else {
          fputc( nl, DSPEW_STREAM );
          if (nl == '\n') { pindent( (level+1)*INDENTSZ ); }
        }
        here = d;
        while (!EQUAL( here, Nil )) {
          if (ISPAIR( here )) {
            dexp de = CAR(here);
            dspew1( de, level+1, nl );
            if (!EQUAL(here,Nil) && !EQUAL( CDR(here), Nil )) {
              if (hor) {
                fprintf( DSPEW_STREAM, ", " );
              } else {
                fputc( ',', DSPEW_STREAM );
                fputc( nl, DSPEW_STREAM );
                if (nl == '\n') { pindent( (level+1)*INDENTSZ ); }
              }
            }
            here = CDR(here);
          } else {
            fprintf( DSPEW_STREAM, ". " );
            dspew1( here, level+1, nl );
            break;
          }
        }
        if (hor) {
        } else {
          fputc( nl, DSPEW_STREAM );
          if (nl == '\n') { pindent( level*INDENTSZ ); }
        }
        fprintf( DSPEW_STREAM, "]" );
      } else if (ISSYMBOL( d )) {
        //printf( "\'" );
        fprintf( DSPEW_STREAM, "%s", SYMSTRING(d) );
      } else {
        fprintf( DSPEW_STREAM, "%s(", CONSCTORS(d) );
        if (hor) {
          fputc( ' ', DSPEW_STREAM );
        } else {
          fputc( nl, DSPEW_STREAM );
          if (nl == '\n') { pindent( (level+1)*INDENTSZ ); }
        }
        FORCTOR (d,de) {
          dspew1( de, level+1, nl );
          if (deinx<CONSCOUNT(d)-1) {
            fputc( ',', DSPEW_STREAM );
            if (hor) {
              fputc( ' ', DSPEW_STREAM );
            } else {
              fputc( nl, DSPEW_STREAM );
              if (nl == '\n') { pindent( (level+1)*INDENTSZ ); }
            }
          }
        }
        if (hor) {
          fprintf( DSPEW_STREAM, " )" );
        } else {
          fputc( nl, DSPEW_STREAM );
          if (nl == '\n') { pindent( level*INDENTSZ ); }
          fprintf( DSPEW_STREAM, ")" );
        }
      }
      break;
    default:
      err(( "??" ));
      break;
  }
}

void dspew( dexp d )
{
  dspew1( d, 0, '\n' );
  fputc( '\n', DSPEW_STREAM );
}

void sldspew( dexp d )
{
  dspew1( d, 0, ' ' );
}

void dspew_indent( dexp d, int indent )
{
  dspew1( d, indent, '\n' );
  fputc( '\n', DSPEW_STREAM );
}

void ndspew( dexp d )
{
  if (d) {
    dspew( d );
  } else {
    spew(( "[NULL]\n" ));
  }
}

void dspew_file( dexp d, char *filename )
{
  io_redirect_stdout( filename );
  dspew( d );
  io_restore_stdout();
}

void lspew( char *s, dexp e )
{
  spew(( "%s ", s ));
  sldspew( e );
  spew(( "\n" ));
}

void compspew( char *s, dexp e0, dexp e1 )
{
  spew(( "---- compare -- %s -----\n", s ));
  dspew( e0 );
  spew(( "+++\n" ));
  dspew( e1 );
  spew(( "-----\n" ));
}
