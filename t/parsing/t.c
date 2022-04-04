// $Id: t.c,v 1.2 2004/08/06 14:24:51 greg Exp $

#define ANOLINE

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../dexp.h"
#include "../../io.h"
#include "../../pt.h"
#include "../../outline.h"

int main( void )
{
  dexp input = io_read_file( "t/parsing/input.k" );
  dspew( pt_parse( input ) );
  return 0;
}
