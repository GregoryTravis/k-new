// $Id: sexp.h,v 1.14 2002/10/22 20:33:19 Administrator Exp $

#ifndef _sexp_h_
#define _sexp_h_

#include <stdio.h>

#include "a.h"
#include "strm.h"

/*
  Manifest types:
    int    (bitcode 1)
    float  (bitcode 10)

  Heap types:  (bitcode 00)
    symbol
    cons
    hash
    obj
*/

typedef enum sexp_types {
  SEXP_MIN=1,
  SEXP_NIL=SEXP_MIN,
  SEXP_SYMBOL,
  SEXP_INTEGER,
  SEXP_FLOAT,
  SEXP_CONS,
  SEXP_HASH,
  SEXP_OBJ,
  SEXP_NATIVE,
  SEXP_BOOLEAN,
  SEXP_CLOSURE,
  SEXP_STRING,
  SEXP_MAX=SEXP_STRING
} sexp_types ;

typedef int sexp;

typedef struct hashentry {
  char *name;
  sexp value;
} hashentry ;

typedef sexp (*sexp_native)( sexp arglist );

typedef struct sexp_heap {
  int type;
  union {
    struct {
      char *name;
    } symbol;

    struct {
      int value;
    } integer;

    struct {
      sexp car;
      sexp cdr;
    } cons;

    struct {
      int size;
      hashentry *entries;
    } hash;

    struct {
      void *obj;
    } obj;

    struct {
      sexp_native native;
      char *funcname;
    } native;

    struct {
      sexp code;
      sexp env;
      char *name;
    } closure;

    struct {
      char *string;
    } string;
  } contents;

  sexp properties;
} sexp_heap ;

#include "sbuild.h"
#include "sparse.h"

#define SEXP_NUM_TAG_BITS (2)
#define SEXP_TAG_BIT_MASK ((1<<(SEXP_NUM_TAG_BITS))-1)
#define SEXP_INTEGER_TAG (0x01)
#define SEXP_FLOAT_TAG (0x02)

#define SEXP_IS_INTEGER(s) ( ((s)&SEXP_INTEGER_TAG) == SEXP_INTEGER_TAG )
#define SEXP_IS_FLOAT(s) ( ((s)&SEXP_FLOAT_TAG) == SEXP_FLOAT_TAG )
#define SEXP_IS_MANIFEST(s) ((s)&SEXP_TAG_BIT_MASK)

#define SEXP_HEAP(s) ((sexp_heap*)(s))

#define SEXP_HEAP_TYPE(s) (A((s)),SEXP_HEAP((s))->type)
#define SEXP_TYPE(s) \
  (SEXP_IS_MANIFEST((s)) ? \
    (SEXP_IS_INTEGER((s)) ? (SEXP_INTEGER) : (SEXP_IS_FLOAT((s)) ? (SEXP_FLOAT) : A(0))) : \
      (SEXP_HEAP_TYPE((s))))
#define SEXP_TYPE_OK(t) ((t)>=SEXP_MIN && (t)<=SEXP_MAX)
#define SEXP_OK(s) (((s)!=0)&&(SEXP_TYPE_OK(SEXP_TYPE((s)))))

#define SEXP_IS_NIL(s) (A((s)),((s)==nil))
#define SEXP_IS_SYMBOL(s) (A((s)),(SEXP_TYPE((s))==SEXP_SYMBOL))
#define SEXP_IS_CONS(s) (A((s)),(SEXP_TYPE((s))==SEXP_CONS))
#define SEXP_IS_HASH(s) (A((s)),(SEXP_TYPE((s))==SEXP_HASH))
#define SEXP_IS_OBJ(s) (A((s)),(SEXP_TYPE((s))==SEXP_OBJ))
#define SEXP_IS_NATIVE(s) (A((s)),(SEXP_TYPE((s))==SEXP_NATIVE))
#define SEXP_IS_BOOLEAN(s) (A((s)),(SEXP_TYPE((s))==SEXP_BOOLEAN))
#define SEXP_IS_CLOSURE(s) (A((s)),(SEXP_TYPE((s))==SEXP_CLOSURE))
#define SEXP_IS_STRING(s) (A((s)),(SEXP_TYPE((s))==SEXP_STRING))

#define SEXP_MKINT(i) (((i)<<1)|SEXP_INTEGER_TAG)
#define SEXP_MKFLOAT(f) ( (((sexp)(f))&~SEXP_TAG_BIT_MASK) | SEXP_FLOAT_TAG )
#define SEXP_MKOBJ(o) (mkobj((o)))
#define SEXP_MKNATIVE(n) (mknative(&(n),#n))
#define SEXP_MKBOOLEAN(b) ((b)?true:false)
#define SEXP_MKCLOSURE(c,e,n) (mkclosure((c),(e),(n)))
#define SEXP_MKSTRING(s) (mkstring((s)))
#define SEXP_GET_INTEGER(s) (A(SEXP_IS_INTEGER((s))),(((int)(s))>>1))
#define SEXP_GET_FLOAT(s) (A(SEXP_IS_FLOAT((s))),((float)((s)&~SEXP_FLOAT_TAG)))
#define SEXP_GET_OBJ(s) (A(SEXP_IS_OBJ((s))),(((sexp_heap*)(s))->contents.obj.obj))
#define SEXP_GET_NATIVE(s) (A(SEXP_IS_NATIVE((s))),(((sexp_heap*)(s))->contents.native.native))
#define SEXP_GET_NATIVE_FUNCNAME(s) (A(SEXP_IS_NATIVE((s))),(((sexp_heap*)(s))->contents.native.funcname))
#define SEXP_GET_BOOLEAN(s) (A(SEXP_IS_BOOLEAN((s))),((s)==true))
#define SEXP_GET_CLOSURE_CODE(s) (A(SEXP_IS_CLOSURE((s))),(((sexp_heap*)(s))->contents.closure.code))
#define SEXP_GET_CLOSURE_ENV(s) (A(SEXP_IS_CLOSURE((s))),(((sexp_heap*)(s))->contents.closure.env))
#define SEXP_GET_CLOSURE_NAME(s) (A(SEXP_IS_CLOSURE((s))),(((sexp_heap*)(s))->contents.closure.name))
#define SEXP_GET_STRING(s) (A(SEXP_IS_STRING((s))),(((sexp_heap*)(s))->contents.string.string))

#define SEXP_PROPERTIES(s) (A((s) && !SEXP_IS_MANIFEST((s))),(((sexp_heap*)(s))->properties))

#define SEXP_STRING_LENGTH(s) (strlen(SEXP_GET_STRING((s))))

#define STR(s) (SEXP_IS_SYMBOL(s),(SEXP_HEAP((s))->contents.symbol.name))
#define S(s) (mksym(#s))
#define EQ(s0,s1) ((SEXP_IS_SYMBOL((s0))&&SEXP_IS_SYMBOL((s1))) ? \
                   (!strcmp(STR((s0)),STR((s1)))) : ((s0)==(s1)))

sexp cons( sexp car, sexp cdr );
#define car(s) (A(SEXP_IS_CONS((s))),SEXP_HEAP((s))->contents.cons.car)
#define cdr(s) (A(SEXP_IS_CONS((s))),SEXP_HEAP((s))->contents.cons.cdr)

/*
#define caar(s) (car(car((s))))
#define cadr(s) (car(cdr((s))))
#define cdar(s) (cdr(car((s))))
#define cddr(s) (cdr(cdr((s))))
#define caddr(s) (car(cddr(s)))
*/

sexp caar( sexp s );
sexp cadr( sexp s );
sexp cdar( sexp s );
sexp cddr( sexp s );
sexp caddr( sexp s );

sexp mkobj( void *obj );
sexp mknative( sexp_native native, char *funcname );
sexp mkclosure( sexp code, sexp env, char *name );
sexp mkstring( char *string );

#define SEXP_IS_ATOM(s) (A(SEXP_OK((s))), !SEXP_IS_CONS((s)))

#define SEXP_STATIC_SEXP(varname,type) \
  static sexp_heap __##varname = { type, NULL, CONST_NIL }; sexp varname = (sexp)&__##varname

#define SEXP_STATIC_SYMBOL(varname,symname) \
  sexp_heap _##varname = { SEXP_SYMBOL, #symname, CONST_NIL }; sexp varname = (sexp)&_##varname

extern sexp nil;
extern sexp_heap _nil;
#define CONST_NIL ((sexp)&(_nil))
extern sexp true;
extern sexp false;

#define L1(a) (cons((a),nil))
#define L2(a,b) (cons((a),L1((b))))
#define L3(a,b,c) (cons((a),L2((b),(c))))
#define L4(a,b,c,d) (cons((a),L3((b),(c),(d))))
#define L5(a,b,c,d,e) (cons((a),L4((b),(c),(d),(e))))
#define L6(a,b,c,d,e,f) (cons((a),L4((b),(c),(d),(e),(f))))

sexp mksym( char *name );

void sexp_pp_stream( ostrm *ost, sexp s, int oneline);
void sexp_pp( sexp s );
void sexp_dump( sexp s );
void sexp_dump_stream( FILE *stream, sexp s );
void sexp_dump_file( char *filename, sexp s );
char *sexp_dump_string( sexp s );

void shav_install_obj_dumper( int (*dumper)( ostrm *ost, void * ) );

int length( sexp list );

sexp append( sexp lyst1, sexp lyst2 );
sexp snoc( sexp rdc, sexp rac );
sexp assoc( sexp key, sexp alist );

void setcar( sexp pair, sexp car );
void setcdr( sexp pair, sexp cdr );
sexp zipper( sexp cars, sexp cdrs );

void sexp_dump_fancy( char *message, sexp sexp );
#define SD(s) sexp_dump_fancy(#s,(s))
#define SM(m,s) sexp_dump_fancy(#m,(s))

// Iterators
#define FORLIST(_elem,_list,_code)                               \
  do {                                                           \
    sexp __list = _list, _cursor;                                \
    for (_cursor=__list; _cursor!=nil; _cursor=cdr( _cursor )) { \
      sexp _elem;                                                \
                                                                 \
      A(SEXP_IS_CONS( _cursor ));                                \
                                                                 \
      _elem = car( _cursor );                                    \
                                                                 \
      {                                                          \
        _code                                                    \
      }                                                          \
    }                                                            \
  } while (0)

#endif /* _sexp_h_ */
