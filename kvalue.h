// $Id: kvalue.h,v 1.3 2002/08/21 16:03:52 Administrator Exp $

#ifndef _kvalue_h_
#define _kvalue_h_

#include "shav.h"

#include "kstruct.h"
#include "klayer.h"

/*
  Manifest types:
    int    (bitcode 1)
    float  (bitcode 10)

  Heap types:  (bitcode 00)
    atom
    cons cell
    vector
    hash
    string
    char

*/

#define KV_NUM_TAG_BITS (2)
#define KV_TAG_BIT_MASK ((1<<(KV_NUM_TAG_BITS))-1)
#define KV_INT_TAG (0x01)
#define KV_FLOAT_TAG (0x02)

#define KV_NIL (0)

typedef enum {
  KINT,
  KFLOAT,
  KATOM,
  KCONS,
  KCLOSURE,

  KMIN=KINT,
  KMAX=KCLOSURE
} kvalue_type;

typedef struct kvalue_heap {
  int type;
} kvalue_heap ;

typedef struct kvalue_atom {
  int type;
  char *name;
} kvalue_atom ;

typedef struct kvalue_cons {
  int type;
  kvalue car, cdr;
} kvalue_cons ;

typedef struct kvalue_closure {
  int type;
  struct klayer *env;
  shav *code;
  char *name;
} kvalue_closure ;

#define KV_MKINT(i) (((i)<<1)|KV_INT_TAG)
#define KV_MKFLOAT(f) ( ((f)&~KV_TAG_BIT_MASK) | KV_FLOAT_TAG )
#define KV_MKATOM(s) kv_mkatom( (s) )
#define KV_MKCONS(car,cdr) kv_mkcons( (car), (cdr) )
#define KV_MKCLOSURE(layer,code) kv_mkclosure( (layer), (code) )

#define KV_INTP(v) (((v)&0x1)==KV_INT_TAG)
#define KV_FLOATP(v) (((v)&0x11)==KV_FLOAT_TAG)
#define KV_HEAPP(v) (((v)&KV_TAG_BIT_MASK)==0)
#define KV_HEAP_TYPE(v) (A(v),A(KV_HEAPP(v)), ( ((kvalue_heap*)(v))->type ))
#define KV_CONSP(v) (KV_HEAP_TYPE(v)==KCONS)
#define KV_ATOMP(v) (KV_HEAP_TYPE(v)==KATOM)
#define KV_CLOSUREP(v) (KV_HEAP_TYPE(v)==KCLOSURE)

#define KV_CAR(c) (A(KV_CONSP((c))),( ((kvalue_cons*)(c))->car ))
#define KV_CDR(c) (A(KV_CONSP((c))),( ((kvalue_cons*)(c))->cdr ))

#define KV_TYPE(v) (KV_INTP((v))?(KINT):(KV_FLOATP((v))?(KFLOAT):(KV_HEAP_TYPE((v)))))
#define KV_TYPEOK(v) (KV_TYPE((v))>=KMIN && KV_TYPE((v))<=KMAX)

#define KV_OK(v) ((v)&&KV_TYPEOK((v)))

#define KV_ATOMIC(v) (KV_INTP((v)) || KV_FLOATP((v)) || KV_ATOMP((v)))

/* Note, these safety checks are only on for debug.  You MUST
   check explicitly before using them.  Always. */
#define KV_GET_INT(v) ((A(KV_INTP(v))),((int)((v)>>1)))
#define KV_GET_FLOAT(v) ((A(KV_FLOATP(v))),((float)((v)&~0x1)))
#define KV_GET_CONS(v) (A(KV_CONSP(v)),(kvalue_cons*)(v))
#define KV_GET_ATOM(v) (A(KV_ATOMP(v)),(kvalue_atom*)(v))
#define KV_GET_CLOSURE(v) (A(KV_CLOSUREP(v)),(kvalue_closure*)(v))

void k_value_init( void );

kvalue kv_mkatom( char *name );
kvalue kv_mkcons( kvalue car, kvalue cdr );
kvalue kv_mkclosure( struct klayer *env, shav *code );
void kv_dump( kvalue value );

void kv_set_closure_name( kvalue closure, char *name );

#endif /* _kvalue_h_ */
