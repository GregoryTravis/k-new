/* $Id: spew.h,v 1.1 2002/08/05 16:00:12 Administrator Exp $ */

#ifndef _spew_h_
#define _spew_h_

#define SPEW_ON

#ifdef SPEW_ON

#define spew(a) spew_do a
#define spew_tab(s,t) spew_tab_do(s,t)

void spew_do( int slot, char *f, ... );
void spew_tab_do( int slot, int tab );

#define SPEWB(code) do code while (0)

#else

#define spew(a)
#define spew_tab(s,t)

#define SPEWB(code) do {} while (0)

#endif

#define err(a) err_do a
#define warn(a) warn_do a

void warn_do( char *f, ... );
void err_do( char *f, ... );

#define SPEWSLOT(slot) slot
enum spew_slot {
#include "spewslot.i"
} ;

typedef struct spew_slot_info {
    char *name;
    enum spew_slot slot;
} spew_slot_info;

spew_slot_info spew_slot_infos[slast+1];

typedef enum spew_slot spew_slot;

#endif /* _spew_h_ */
