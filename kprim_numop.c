// $Id: kprim_numop.c,v 1.5 2002/10/08 18:43:00 Administrator Exp $

#include "mem.h"

#include "kprim_numop.h"

typedef int boolint;
typedef char *string;

#define DEFPRIMNUMOP(t,name,type) \
  static type __numop_##name##_##type( type a, type b ) \
  { \
    return a t b; \
  }
#define DEFNUMOPWRAPPER(name) \
  sexp numop_##name( sexp arglist ) \
  { \
    return numop_generic( arglist, &__numop_##name##_##int, &__numop_##name##_##float, #name ); \
  }

#define NUMOP(t,name) \
  DEFPRIMNUMOP(t,name,int) \
  DEFPRIMNUMOP(t,name,float) \
  DEFNUMOPWRAPPER(name)

static sexp numop_generic( sexp arglist, int (*intp)( int, int ), float (*floatp)( float, float ), char *name )
{
  sexp a, b;
  int at, bt;

  if (length( arglist ) != 2) {
    sexp_dump( arglist );
    kerr( "Wrong number of args for %s", name );
  }
  KERRPUNTV(nil);

  a = car( arglist );
  b = cadr( arglist );

  A(SEXP_OK(a));
  A(SEXP_OK(b));

  at = SEXP_TYPE( a );
  bt = SEXP_TYPE( b );

  if (at==SEXP_INTEGER && bt==SEXP_INTEGER) {
    int av = SEXP_GET_INTEGER( a );
    int bv = SEXP_GET_INTEGER( b );
    int sumv = (*intp)( av, bv );
    sexp sum = SEXP_MKINT( sumv );
    return sum;
  } else if ((at==SEXP_INTEGER||at==SEXP_FLOAT) &&
             (bt==SEXP_INTEGER||bt==SEXP_FLOAT)) {
    float av = at==SEXP_INTEGER ? SEXP_GET_INTEGER( a ) : SEXP_GET_FLOAT( a );
    float bv = bt==SEXP_INTEGER ? SEXP_GET_INTEGER( b ) : SEXP_GET_FLOAT( b );
    float sumv = (*floatp)( av, bv );
    sexp sum = SEXP_MKFLOAT( sumv );
    return sum;
  } else {
    sexp_dump( a );
    sexp_dump( b );
    kerr( "Bad argument types for %s", name );
  }
  KERRPUNTV(nil);
  return nil;
}

#define DEFPRIMCONDOP(t,name,type) \
  static sexp __condop_##name##_##type( type a, type b ) \
  { \
    return a t b ? true : false; \
  }

#define DEFSTRINGPRIMCONDOP(t,name) \
  static sexp __condop_##name##_##string( char *a, char *b ) \
  { \
    return (!strcmp( a, b )) ? true : false; \
  }

#define DEFCONDOPWRAPPER(name) \
  sexp condop_##name( sexp arglist ) \
  { \
    return condop_generic( arglist, &__condop_##name##_##int, &__condop_##name##_##float, #name ); \
  }

#define DEFGCONDOPWRAPPER(name) \
  sexp condop_##name( sexp arglist ) \
  { \
    return gcondop_generic( arglist, &__condop_##name##_##int, &__condop_##name##_##float, \
      &__condop_##name##_##boolint, &__condop_##name##_##sexp, \
      &__condop_##name##_##string, #name ); \
  }

#define CONDOP(t,name) \
  DEFPRIMCONDOP(t,name,int) \
  DEFPRIMCONDOP(t,name,float) \
  DEFCONDOPWRAPPER(name)

#define GCONDOP(t,name) \
  DEFPRIMCONDOP(t,name,int) \
  DEFPRIMCONDOP(t,name,float) \
  DEFPRIMCONDOP(t,name,boolint) \
  DEFPRIMCONDOP(t,name,sexp) \
  DEFSTRINGPRIMCONDOP(t,name) \
  DEFGCONDOPWRAPPER(name)

static sexp condop_generic( sexp arglist, sexp (*intp)( int, int ),
    sexp (*floatp)( float, float ), char *name )
{
  sexp a, b;
  int at, bt;

  if (length( arglist ) != 2) {
    sexp_dump( arglist );
    kerr( "Wrong number of args for %s", name );
  }
  KERRPUNTV(nil);

  a = car( arglist );
  b = cadr( arglist );

  A(SEXP_OK(a));
  A(SEXP_OK(b));

  at = SEXP_TYPE( a );
  bt = SEXP_TYPE( b );

  if (at==SEXP_INTEGER && bt==SEXP_INTEGER) {
    int av = SEXP_GET_INTEGER( a );
    int bv = SEXP_GET_INTEGER( b );
    return (*intp)( av, bv );
  } else if ((at==SEXP_INTEGER||at==SEXP_FLOAT) &&
             (bt==SEXP_INTEGER||bt==SEXP_FLOAT)) {
    float av = at==SEXP_INTEGER ? SEXP_GET_INTEGER( a ) : SEXP_GET_FLOAT( a );
    float bv = bt==SEXP_INTEGER ? SEXP_GET_INTEGER( b ) : SEXP_GET_FLOAT( b );
    return (*floatp)( av, bv );
  } else {
    sexp_dump( a );
    sexp_dump( b );
    kerr( "Bad argument types for %s", name );
  }
  KERRPUNTV(nil);
  return nil;
}

static sexp gcondop_generic( sexp arglist, sexp (*intp)( int, int ),
    sexp (*floatp)( float, float ), sexp (*boolintp)( boolint, boolint ),
    sexp (*sexpp)( sexp, sexp ), sexp (*stringp)( string, string ), char *name )
{
  sexp a, b;
  int at, bt;

  if (length( arglist ) != 2) {
    sexp_dump( arglist );
    kerr( "Wrong number of args for %s", name );
  }
  KERRPUNTV(nil);

  a = car( arglist );
  b = cadr( arglist );

  A(SEXP_OK(a));
  A(SEXP_OK(b));

  at = SEXP_TYPE( a );
  bt = SEXP_TYPE( b );

  if (at==SEXP_INTEGER && bt==SEXP_INTEGER) {
    int av = SEXP_GET_INTEGER( a );
    int bv = SEXP_GET_INTEGER( b );
    return (*intp)( av, bv );
  } else if ((at==SEXP_INTEGER||at==SEXP_FLOAT) &&
             (bt==SEXP_INTEGER||bt==SEXP_FLOAT)) {
    float av = at==SEXP_INTEGER ? SEXP_GET_INTEGER( a ) : SEXP_GET_FLOAT( a );
    float bv = bt==SEXP_INTEGER ? SEXP_GET_INTEGER( b ) : SEXP_GET_FLOAT( b );
    return (*floatp)( av, bv );
  } else if (at==SEXP_BOOLEAN && bt==SEXP_BOOLEAN) {
    boolint av = SEXP_GET_BOOLEAN( a );
    boolint bv = SEXP_GET_BOOLEAN( b );
    return (*boolintp)( av, bv );
  } else if (at==SEXP_STRING && bt==SEXP_STRING) {
    string av = SEXP_GET_STRING( a );
    string bv = SEXP_GET_STRING( b );
    return (*stringp)( av, bv );
  } else if (at==SEXP_SYMBOL && bt==SEXP_SYMBOL) {
    return (*stringp)( STR( a ), STR( b ) );
  } else {
    return (*sexpp)( a, b );
  }
  KERRPUNTV(nil);
  return nil;
}

NUMOP(-,minus)
NUMOP(*,times)
NUMOP(/,divided)

GCONDOP(==,dequals);
GCONDOP(!=,dnequals);
CONDOP(<,lt);
CONDOP(>,gt);
CONDOP(<=,lte);
CONDOP(>=,gte);

sexp numop_plus( sexp arglist )
{
  sexp a, b;
  int at, bt;
  static char *name = "+";

  if (length( arglist ) != 2) {
    sexp_dump( arglist );
    kerr( "Wrong number of args for %s", name );
  }
  KERRPUNTV(nil);

  a = car( arglist );
  b = cadr( arglist );

  A(SEXP_OK(a));
  A(SEXP_OK(b));

  at = SEXP_TYPE( a );
  bt = SEXP_TYPE( b );

  if (at==SEXP_INTEGER && bt==SEXP_INTEGER) {
    int av = SEXP_GET_INTEGER( a );
    int bv = SEXP_GET_INTEGER( b );
    int sumv = av+bv;
    sexp sum = SEXP_MKINT( sumv );
    return sum;
  } else if ((at==SEXP_INTEGER||at==SEXP_FLOAT) &&
             (bt==SEXP_INTEGER||bt==SEXP_FLOAT)) {
    float av = at==SEXP_INTEGER ? SEXP_GET_INTEGER( a ) : SEXP_GET_FLOAT( a );
    float bv = bt==SEXP_INTEGER ? SEXP_GET_INTEGER( b ) : SEXP_GET_FLOAT( b );
    float sumv = av+bv;
    sexp sum = SEXP_MKFLOAT( sumv );
    return sum;
  } else if (at==SEXP_STRING || bt==SEXP_STRING) {
    char *s0, *s1, *concat, len0, len1;
    int order=0;
    if (at==SEXP_STRING && bt==SEXP_STRING) {
      s0 = STR(a);
      s1 = STR(b);
    } else {
      static char buf[8192];
      char *string = at==SEXP_STRING ? STR(a) : STR(b);
      sexp other = at==SEXP_STRING ? b : a;
      sexp other_type = at==SEXP_STRING ? bt : at;
      order = at==SEXP_STRING;
      if (other_type==SEXP_INTEGER) {
        sprintf( buf, "%d", SEXP_GET_INTEGER(other) );
      } else if (other_type==SEXP_FLOAT) {
        sprintf( buf, "%d", SEXP_GET_FLOAT(other) );
      } else if (other_type==SEXP_SYMBOL) {
        sprintf( buf, "%s", STR(other) );
      } else {
        sprintf( buf, "%s", sexp_dump_string( other ) );
      }
      s0 = order ? string : buf;
      s1 = order ? buf : string;
    }

    len0 = strlen( s0 );
    len1 = strlen( s1 );

    concat = malik( len0+len1+1 );

    strcpy( concat, s0 );
    strcpy( concat+len0, s1 );

    return SEXP_MKSTRING( concat );
  } else {
    sexp_dump( a );
    sexp_dump( b );
    kerr( "Bad argument types for %s", name );
  }
  KERRPUNTV(nil);
  return nil;
}
