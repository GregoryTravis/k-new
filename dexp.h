// $Id: dexp.h,v 1.8 2005/02/25 19:23:36 greg Exp $

#ifndef _dexp_h_
#define _dexp_h_

#include <string.h>
#include "a.h"
#include "mem.h"

// Forward declarations for hash.h
struct dexps;
typedef struct dexps *dexp;

#include "dspew.h"
#include "hash.h"
#include "match.h"

typedef enum dexp_type {
  dexp_error=0,
  dexp_char=1,
  dexp_int=2,
  dexp_float=3,
  dexp_double=4,
  dexp_string=5,
  dexp_array=6,
  dexp_tuple=7,
  dexp_map=8,
  dexp_cons=9,

  dexp_min=dexp_char,
  dexp_max=dexp_cons,
} dexp_type;

typedef struct dexps {
  dexp_type type;

  union {
    char char_v;
    int int_v;
    float float_v;
    double double_v;
    char *string_v;
    struct {
      int size;
      dexp *elems;
    } array_v;
    struct {
      int size;
      dexp *elems;
    } tuple_v;
    hash *map_v;
    struct {
      char *ctor;
      int nargs;
      dexp args[0];
    } cons_v;
  } v;
  // Must be nothing after the union, cuz of the 0-len arrays

} dexps;

#define DEXP_ARGLIST_SENTINEL ((void*)0xFFFFFFFF)

#define ISTYPE(d,t) ((d) && (d)->type==(t))
#define MUSTTYPE(d,t) (A(MUSTTYPE(d,t)))

#define ISCHAR(d) (ISTYPE(d,dexp_char))
#define ISINT(d) (ISTYPE(d,dexp_int))
#define ISFLOAT(d) (ISTYPE(d,dexp_float))
#define ISDOUBLE(d) (ISTYPE(d,dexp_double))
#define ISSTRING(d) (ISTYPE(d,dexp_string))
#define ISMAP(d) (ISTYPE(d,dexp_map))
#define ISARRAY(d) (ISTYPE(d,dexp_array))
#define ISTUPLE(d) (ISTYPE(d,dexp_tuple))
#define ISCONS(d) (ISTYPE(d,dexp_cons))

#define ISAGG(d) (ISCONS((d)) || ISTUPLE((d)) || ISARRAY((d)) || ISMAP((d)))

#define PTR(d) (I((int)(d)))

#define ARRAYSIZE(d) (A(ISARRAY((d))),(d)->v.array_v.size)
#define ARRAYINXOK(d,i) \
  (A(ISARRAY((d))),((i>=0) && i<ARRAYSIZE((d))))
#define ARRAYLVAL(d,i)                        \
  (A(ISARRAY((d))),                           \
   RA( ((i>=0) && (i<ARRAYSIZE((d)))),        \
       ("Array index %d out of range %d..%d", \
        (i), 0, (d)->v.array_v.size) ),       \
   (d)->v.array_v.elems[i])

#define TUPLESIZE(d) (A(ISTUPLE((d))),(d)->v.tuple_v.size)
#define TUPLEINXOK(d,i) \
  (A(ISTUPLE((d))),((i>=0) && i<TUPLESIZE((d))))
#define TUPLELVAL(d,i)                        \
  (A(ISTUPLE((d))),                           \
   RA( ((i>=0) && (i<TUPLESIZE((d)))),        \
       ("Tuple index %d out of range %d..%d", \
        (i), 0, (d)->v.tuple_v.size) ),       \
   (d)->v.tuple_v.elems[i])

#define MAPGET(m,k) (A(ISMAP(m)),hashget((m)->v.map_v,(k)))
#define MAPPUT(m,k,val) (A(ISMAP(m)),hashput((m)->v.map_v,(k), (val)))
#define MAPDEL(m,k) (A(ISMAP(m)),hashdel((m)->v.map_v,(k)))
#define MAPHASH(__m) (A(ISMAP((__m))),(__m)->v.map_v)
#define MAPSIZE(__m) (A(ISMAP((__m))),(__m)->v.map_v->num_entries)

#define CONSCTORS(d) (A(ISCONS((d))),(d)->v.cons_v.ctor)
#define CONSCTOR(d) (mksymbol(CONSCTORS((d))))
#define ISCTOR(d,s) (ISCONS((d)) && (!strcmp((d)->v.cons_v.ctor,(s))))
#define CONSCOUNT(d) (A(ISCONS((d))),(d)->v.cons_v.nargs)
#define CONSELEM(d,i)                           \
  (A(ISCONS((d))),                              \
   RA( ((i)>=0 && (i)<(d)->v.cons_v.nargs),     \
       ("Ctor index  %d out of range %d..%d", \
        (i),0,(d)->v.cons_v.nargs) ),           \
  (d)->v.cons_v.args[i])

#define ISSYMBOL(d) (ISCONS((d)) && CONSCOUNT(d)==0)
#define SYMSTRING(d) (CONSCTORS((d)))

dexp mkchar( char c );
dexp mkint( int i );
dexp mkfloat( float f );
dexp mkdouble( double d );
dexp mkstring( char *s );
dexp mkarray( int size );
dexp mktuple( int size );
dexp mkmap1( int dummy, ... );
#define mkmap( ... ) mkmap1( 0, __VA_ARGS__, DEXP_ARGLIST_SENTINEL )
dexp mkcons1( char *ctor, ... );
#define mkcons( ... ) mkcons1( __VA_ARGS__, DEXP_ARGLIST_SENTINEL )

#define mksymbol(s) (mkcons((s)))

#define EQUAL(d0,d1) dexp_equal( (d0), (d1) )
int dexp_equal( dexp d0, dexp d1 );

// List stuff
#define ISPAIR(d) (ISCTOR((d),"Cons") && CONSCOUNT((d))==2)
#define ISNIL(d) (ISCTOR((d),"Nil") && CONSCOUNT((d))==0)
dexp mklist1( int dummy, ... );
#define mklist( ... ) mklist1( 0 , __VA_ARGS__, DEXP_ARGLIST_SENTINEL )
dexp _Nil( void );
#define Nil (_Nil())
#define CAR(d) (A(ISPAIR((d))), CONSELEM(d,0))
#define CDR(d) (A(ISPAIR((d))), CONSELEM(d,1))
#define CADR(d) (CAR(CDR((d))))
#define CDDR(d) (CDR(CDR((d))))
//#define CONS(a,d) mkcons( "Cons", (a), (d) )
#define ISLIST(__l) (ISPAIR((__l)) || ISNIL((__l)))
#define CONS(a,d) (mkcons( "Cons", (a), (d) ))
int dexp_list_length( dexp list );
dexp list2ctor( dexp ctor, dexp list );
dexp args2list( dexp ctor );

#define gC(d) (A(ISCHAR((d))),(d)->v.char_v)
#define gI(d) (A(ISINT((d))),(d)->v.int_v)
#define gF(d) (A(ISFLOAT((d))),(d)->v.float_v)
#define gD(d) (A(ISDOUBLE((d))),(d)->v.double_v)
#define gST(d) (A(ISSTRING((d))),(d)->v.string_v)
#define gK(d,i) (CONSELEM((d),(i)))

#define TYPEOK(d) ((d)->type>=dexp_min && (d)->type<=dexp_max)
void slow_dck( dexp d );
#define MEM_DCK(d) AMEM_ADDR_IN_RANGE((d))
//#define SLOW_DCK(d) (slow_dck((d)))
#define SLOW_DCK(d) (1)
#define FAST_DCK(d) (A((d)), MEM_DCK((d)), A(TYPEOK((d))))
#define DCK(d) (FAST_DCK((d)),SLOW_DCK((d)))

// Laziness
#define S(s) (mksymbol((#s)))
#define C(c) (dexp_check_string_len(#c,1),(mkchar((#c[0]))))
#define I(i) (mkint((i)))
#define F(f) (mkfloat((f)))
#define D(d) (mkdouble((d)))
#define ST(s) (mkstring((#s)))
#define AR(size) (mkarray(size))
#define T(size) (mktuple(size))
#define M(...) (mkmap(__VA_ARGS__))
#define EMAP() (M(DEXP_ARGLIST_SENTINEL))
#define K(ctor,...) (mkcons(#ctor,__VA_ARGS__))

#define L(...) (mklist(__VA_ARGS__))
#define ELIST() (L(DEXP_ARGLIST_SENTINEL))

#define CT(d,ctor) ISCTOR((d),#ctor)

#define gM(m,k) MAPGET((m),(k))
#define pM(m,k,val) MAPPUT((m),(k),(val))
#define dM(m,k) MAPDEL((m),(k))
#define gA(d,i) ARRAYLVAL((d),(i))
#define pA(d,i,val) (ARRAYLVAL((d),(i)) = (val))
#define gT(d,i) TUPLELVAL((d),(i))
#define pT(d,i,val) (TUPLELVAL((d),(i)) = (val))

dexp dexp_append( dexp d0, dexp d1 );

// For internal use only
#define pK(d,i,v) ((CONSELEM((d),(i)))=(v))
dexp dexp_make_empty_cons( char *ctor, int size );

int dexp_strlen( dexp s0 );
dexp dexp_char2string( dexp c );
dexp dexp_string2symbol( dexp s );
dexp dexp_char2symbol( dexp c );
dexp dexp_symbol2string( dexp s );
dexp dexp_list2array( dexp list );
dexp dexp_list2tuple( dexp list );
dexp dexp_tosymbol( dexp d );
dexp dexp_tostring( dexp d );
dexp dexp_tointeger( dexp d );
dexp dexp_tochar( dexp d );

#define FORLIST( __list, __elem ) \
  dexp __elem, __elem##_here; \
  for (__elem##_here=__list, \
       (__elem=(EQUAL(__elem##_here,Nil) ? Nil : CAR(__elem##_here)));\
       !EQUAL(__elem##_here,Nil); \
        __elem##_here=CDR(__elem##_here),\
        (__elem=(EQUAL(__elem##_here,Nil) ? Nil : CAR(__elem##_here))))

dexp dexp_mapfun( dexp (*fun)( dexp ), dexp collection );

#define FORARRAY( __array1, __elem ) \
  dexp __array = (__array1), __elem; \
  int __elem##inx; \
  for (__elem##inx=0,__elem = (__elem##inx<ARRAYSIZE(__array)?gA(__array,__elem##inx):Nil); __elem##inx<ARRAYSIZE(__array); ++__elem##inx,__elem = (__elem##inx<ARRAYSIZE(__array) ? gA(__array,__elem##inx) : Nil))

#define FORTUPLE( __tuple1, __elem ) \
  dexp __tuple = (__tuple1), __elem; \
  int __elem##inx; \
  for (__elem##inx=0,__elem = (__elem##inx<TUPLESIZE(__tuple)?gT(__tuple,__elem##inx):Nil); __elem##inx<TUPLESIZE(__tuple); ++__elem##inx,__elem = (__elem##inx<TUPLESIZE(__tuple) ? gT(__tuple,__elem##inx) : Nil))

#define FORMAP(__m,__k,__v) FORHASH(MAPHASH(__m),__k,__v)

#define FORCTOR(__k1,__e) \
  dexp __k = (__k1), __e; \
  int __e##inx; \
  for (__e##inx=0,__e=gK(__k,__e##inx); __e##inx<CONSCOUNT(__k); __e##inx++,__e=(__e##inx<CONSCOUNT(__k) ? gK(__k,__e##inx) : 0))

void dexp_check_string_len( char *s, int len );
void dexp_report( void );
char *typename( dexp d );

extern char *dexp_typenames[dexp_max+1];
void dexp_equal_profiling_report( void );
dexp dexp_array2map_maybe( dexp array );

dexp dexp_nth( dexp list, int n );
#define gL(l,n) (dexp_nth((l),(n)))

dexp dexp_escape( dexp s );
dexp dexp_keys( dexp map );

dexp dexp_reverse( dexp list );

#define NORETURN do { err(( "NORETURN returned!" )); return Nil; } while (0)

#endif /* _dexp_h_ */
