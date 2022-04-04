/* spew.c */

#include <stdarg.h>
#include <stdio.h>
#include "a.h"
#include "mem.h"
#include "strm.h"
#include "spew.h"

void vspew( int slot, char *f, va_list va );

FILE *spewfile=0;

#undef SPEWSLOT
#define SPEWSLOT(slot) { #slot, slot }
spew_slot_info spew_slot_infos[slast+1] = {
#include "spewslot.i"
} ;

#define SLOTON(a) spew_gates[(a)]

bool spew_initted;
bool spew_gates[slast];
bool spew_flush = 1;

#define LINE 0x40
char line[LINE];

void spew_init( void )
{
    int i;
    FILE *fp;

    spew_initted = 1;

    spew_gates[son] = 1;

    fp = fopen( "spew.rc", "r" );
    if (fp == NULL) return;
    for (i=0; i<slast; ++i)
      spew_gates[i] = 0;

    while (fgets( line, LINE, fp )) {
	int l;
	l = strlen(line)-1;
	if (line[l]=='\n') line[l]=0;
	for (i=0; i<slast; ++i)
	  if (!strcmp( spew_slot_infos[i].name, line ))
	    spew_gates[i] = line[0]!='!';
    }

    fclose( fp );
}

void spew_do( int slot, char *f, ... )
{
    va_list va;

    if (slot==-1) return;

    if (!spew_initted) spew_init();
    va_start(va,f);
    vspew( slot, f, va );
    va_end(va);
}

void vspew( int slot, char *f, va_list va )
{
  if (spewfile==0)
    spewfile = stdout;

  if ((SLOTON(slot)||!slot) && spewfile!=0) {
    vfprintf( spewfile, f, va );
    if (spew_flush)
      fflush( spewfile );
  }
}

void warn_do( char *f, ... )
{
    va_list va;
    va_start(va,f);
    vspew( son, f, va );
    va_end( va );
}

void err_do( char *f, ... )
{
    va_list va;
    va_start(va,f);
    vspew( son, f, va );
    va_end( va );
    fflush( stdout );
    fflush( stderr );
    exit( 1 );
}

void spew_tab_do( int slot, int tab )
{
  while (tab--)
    spew(( slot, " " ));
}
