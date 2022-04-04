/* $Id: outline.c,v 1.1 2004/08/06 14:14:29 greg Exp $ */

#include <stdarg.h>
#include <stdio.h>
#include "dexp.h"
#include "outline.h"

static int serial=0;
static int level=0;

#define HTML 0

#define fp stdout

static void preamble( void )
{
  if (HTML) {
    static int first=1;
    if (!first) {
      return;
    }
    first = 0;
    fprintf( fp, "<script language=\"javascript\" src=\"toggle.js\" />\n" );
    fprintf( fp, "<pre>\n" );
  }
}

void ospew( char *format, ... )
{
  va_list va;
  va_start(va,format);
  vfprintf( fp, format, va );
  va_end(va);
}

void ospew_title_start( void )
{
  if (HTML) {
    preamble();
    fprintf( fp, "<span id=\"o%d\" onClick=\"toggleChildren( \'o%d\', event )\">", serial, serial );
    fprintf( fp, "<span id=\"o%dpm\">+</span>", serial );
  }
}

void ospew_title_end( void )
{
  if (HTML) {
    static char *colors[2] = { "#e0f0f0", "f0f0e0" };
    char *color = colors[(level%2)];
    fprintf( fp, "<span style=\"border: solid thin #b0b0b0; display:none; position:relative; left:14px; background-color:%s\" id=\"o%dc\">", color, serial );
    serial++;
    level++;
  }
}

void ospew_end( void )
{
  if (HTML) {
    level--;
    fprintf( fp, "</span>" );
    fprintf( fp, "</span>" );
  }
}
