// $Id: sparse.c,v 1.3 2002/08/30 19:42:15 Administrator Exp $

#include <string.h>

#include "mem.h"
#include "sparse.h"

#define sexp_isspace(c) ((c)==' '||(c)=='\t'||(c)=='\n')
#define sexp_isatomchar(c) (!sexp_isspace(c) && ((c)!='(') && ((c)!=')') && ((c)!='.') && (c))

static sexp sexp_parse_sexp( char *string, char **next );

static sexp sexp_parse_list( char *string, char **next )
{
  while (sexp_isspace(*string)) {
    string++;
  }

  if (*string==0) {
    err(( "Sexp syntax error: premature end of sexp in sexp_parse_list()!" ));
    return 0;
  } else if (*string==')') {
    *next = string+1;
    return nil;
  } else if (*string=='.') {
    char *endparen;
    sexp cdr, shouldnil;
    cdr = sexp_parse_sexp( string+1, &endparen );
    shouldnil = sexp_parse_list( endparen, next );
    if (shouldnil != nil) {
      err(( "Bad list-end in %s\n", string ));
    }
    return cdr;
  } else {
    char *tnext;
    sexp car;

    car = sexp_parse_sexp( string, &tnext );
    return cons( car, sexp_parse_list( tnext, next ) );
  }
}

static sexp sexp_parse_string( char *string, char **next )
{
  char *s = string, *nustring, *nus;
  int length = 0;
  int scanning = 1;

  A(string);
  A(next);
  A(*s=='\"');

  while (1) {
    while (1) {
      if (*s!='\"') {
        if (*s=='\\') {
          s++;
          switch (*s) {
            case 'r':
              if (scanning) {
                *nus++ = '\r';
              }
              break;
            case '\"':
              if (scanning) {
                *nus++ = '\"';
              }
              break;
            case '\'':
              if (scanning) {
                *nus++ = '\'';
              }
              break;
            case '0':
              if (scanning) {
                *nus++ = '\0';
              }
              break;
            case 'n':
              if (scanning) {
                *nus++ = '\n';
              }
              break;
            case 0:
              err(( "Sexp syntax error: premature end of string in sexp_parse_string()!" ));
              break;
            default:
              err(( "Sexp syntax error: unknown escape sequence \'\\%c\' in sexp_parse_string()!", *s ));
              break;
          }
        } else {
          if (!scanning) {
            *nus++ = *s;
          }
        }
        s++;
        if (scanning) {
          length++;
        }
      } else {
        break;
      }
    } // inner

    if (scanning) {
      nus = nustring = (char*)malik( length+1 );
      s = string;
      length = 0;
      scanning = 0;
    } else {
      *nus==0;
      A(nus-nustring == s-string && s-string==length);
    }
  } // outer

  return SEXP_MKSTRING( nustring );
}

// assumes null-termination, like everything else
static sexp sexp_parse_atom( char *string, char **next )
{
  char *s = string;
  sexp atom;

  while (sexp_isatomchar( *s ) && s) {
    s++;
  }

  if (*s==0) {
    err(( "Sexp syntax error: premature end of sexp in sexp_parse_atom()!" ));
    return 0;
  }

  {
    int len = s-string;
    if (len==2 && !strncmp( string, "#t", 2 )) {
      atom = true;
    } else if (len==2 && !strncmp( string, "#f", 2 )) {
      atom = false;
    } else if (*s=='\"') {
      atom = sexp_parse_string( s, next );
    } else {
      char *nu = (char*)malik( len+1 );
      memkapi( nu, string, len );
      nu[len] = 0;
      atom = mksym( nu );
    }
  }

  *next = s;

  return atom;
}

static sexp sexp_parse_sexp( char *string, char **next )
{
  while (sexp_isspace(*string) && *string) {
    string++;
  }

  if (*string==0) {
    err(( "Sexp syntax error: premature end of sexp in sexp_parse_sexp()!" ));
    return 0;
  }

  if (*string=='(') {
    return sexp_parse_list( string+1, next );
  } else {
    return sexp_parse_atom( string, next );
  }
}

sexp sexp_parse( char *string )
{
  char *dummy;

  return sexp_parse_sexp( string, &dummy );
}
