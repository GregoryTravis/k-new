/* $Id: mem.h,v 1.2 2002/09/11 20:01:49 Administrator Exp $ */

#ifndef _mem_h_
#define _mem_h_

#define MEM_USE_GC

#define malik(size) (malik_actual(__FILE__,__LINE__,(size)))
#define realik(mem,size) (realik_actual(__FILE__,__LINE__,(mem),(size)))
#define fri(mem) (fri_actual(__FILE__,__LINE__,(mem)))

#define NEW(str) ((str *)cmalik( sizeof(str) ))
#define NEWC(str,n) ((str *)cmalik( sizeof(str)*(n) ))
#define NCNEW(str) ((str *)malik( sizeof(str) ))
#define NCNEWC(str,n) ((str *)malik( sizeof(str)*(n) ))

void *cmalik( int size );

void *malik_actual( char *file, int line, int size );
void *realik_actual( char *file, int line, void *mem, int size );
void fri_actual( char *file, int line, void *mem );
void memkapi( void *dest, void *src, int len );
void strkapi( char *dest, char *src );
void *memfill( void *dest, int c, int n );

char *strdoop( char *s );
char *strkat( char *s0, char *s1 );

#endif /* _mem_h_ */
