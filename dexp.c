/* $Id: dexp.c,v 1.6 2005/02/25 20:08:34 greg Exp $ */

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "a.h"
#include "dexp.h"
#include "hash.h"
#include "mem.h"

static hash *symbol_hash=0;

#define STRING_BUF_SIZE 1024
static char string_buf[STRING_BUF_SIZE];

char *dexp_typenames[dexp_max+1] = {
  "error", "char", "int", "float", "double",
  "string", "array", "tuple", "map", "cons" };

#define COUNT(te) mkcounts[(te)]++
static int mkcounts[dexp_max+1];

static void ensure_symbol_hash_initted( void )
{
  if (!symbol_hash) {
    symbol_hash = makehash( 32 );
  }
}

#define EQUAL_PROFILING 1
#if EQUAL_PROFILING
static int equal_counts[dexp_max+1];
static int unequal_types=0;
# define EQUAL_PROFILE(_type) equal_counts[_type]++;
# define EQUAL_PROFILE_NE() unequal_types++;
#else
# define EQUAL_PROFILE(_type)
# define EQUAL_PROFILE_NE()
#endif

// extra: # of extra bytes to allocate past end
static dexp mkdexp( int extra )
{
  A(extra>=0);
  return (dexp)malik( sizeof(dexps) + extra );
}

dexp mkchar( char c )
{
  dexp d = mkdexp( 0 );
//fprintf( stderr, "MK %d %c\n", c, c );
  d->type = dexp_char;
  d->v.char_v = c;
  COUNT(dexp_char);
  return d;
}

dexp mkint( int i )
{
  dexp d = mkdexp( 0 );
  d->type = dexp_int;
  d->v.int_v = i;
  COUNT(dexp_int);
  return d;
}

dexp mkfloat( float f )
{
  dexp d = mkdexp( 0 );
  d->type = dexp_float;
  d->v.float_v = f;
  COUNT(dexp_float);
  return d;
}

dexp mkdouble( double df )
{
  dexp d = mkdexp( 0 );
  d->type = dexp_double;
  d->v.double_v = df;
  COUNT(dexp_double);
  return d;
}

dexp mkstring( char *s )
{
  dexp d = mkdexp( 0 );
  d->type = dexp_string;
  d->v.string_v = strdoop( s );
  COUNT(dexp_string);
  return d;
}

dexp mkarray( int size )
{
  int i;

  dexp d = mkdexp( size * sizeof( dexp ) );
  d->type = dexp_array;
  d->v.array_v.size = size;
  d->v.array_v.elems = (dexp*)(d+1);

  for (i=0; i<d->v.array_v.size; ++i) {
    pA(d,i,Nil);
  }

  COUNT(dexp_array);
  return d;
}

dexp mktuple( int size )
{
  int i;

  dexp d = mkdexp( size * sizeof( dexp ) );
  d->type = dexp_tuple;
  d->v.tuple_v.size = size;
  d->v.tuple_v.elems = (dexp*)(d+1);

  for (i=0; i<d->v.tuple_v.size; ++i) {
    pT(d,i,Nil);
  }

  COUNT(dexp_tuple);
  return d;
}

dexp mkmap1( int dummy, ... )
{
  va_list va;

  dexp d = mkdexp( 0 );
  d->type = dexp_map;
  d->v.map_v = makehash( 4 );
  va_start( va, dummy );
  while (1) {
    dexp key = va_arg( va, dexp );
    if (key==DEXP_ARGLIST_SENTINEL) {
      break;
    }
    dexp value = va_arg( va, dexp );
    if (value==0 || value==DEXP_ARGLIST_SENTINEL) {
      err(( "Odd # of args to mkmap!" ));
    }

    hashput( d->v.map_v, key, value );
  }
  va_end( va );

  COUNT(dexp_map);
  return d;
}

dexp mkcons1( char *ctor, ... )
{
  va_list va;
  int i, nargs;

  nargs = 0;
  va_start( va, ctor );
  while (va_arg( va, dexp )!=DEXP_ARGLIST_SENTINEL) {
    //A(nargs<8); // just for safety
    nargs++;
  }
  va_end( va );

  dexp d=0;

  // If it is 0-ary, we must canonicalize it.
  if (nargs==0) {
    ensure_symbol_hash_initted();

    static dexp string=0;
    if (!string) {
      string = mkstring( "" );
    }
    string->v.string_v = ctor;
    d = hashget( symbol_hash, string );

    if (!d) {
      d = dexp_make_empty_cons( ctor, nargs );
      hashput( symbol_hash, mkstring(ctor), d );
    }
  } else {
    d = dexp_make_empty_cons( ctor, nargs );
  }

  A(!strcmp( SYMSTRING( d ), ctor ));

  dexp *args = &d->v.cons_v.args[0];
  va_start( va, ctor );
  for (i=0; i<nargs; ++i) {
    args[i] = va_arg( va, dexp );
    DCK(args[i]);
  }
  va_end( va );

  return d;
}

dexp dexp_make_empty_cons( char *ctor, int nargs )
{
  int i;

  dexp d = mkdexp( nargs*sizeof(dexp) );
  d->type = dexp_cons;
  d->v.cons_v.ctor = strdoop( ctor );
  d->v.cons_v.nargs = nargs;

  for (i=0; i<nargs; ++i) {
    pK(d,i,Nil);
  }

  COUNT(dexp_cons);
  return d;
}

dexp mklist1( int dummy, ... )
{
  va_list va;
  dexp list = Nil, end = Nil;

  va_start( va, dummy );
  while (1) {
    dexp elem = va_arg( va, dexp );
    if (elem==DEXP_ARGLIST_SENTINEL) {
      break;
    }

    DCK(elem);

    if (EQUAL( list, Nil )) {
      list = end = CONS( elem, Nil );
    } else {
      CDR( end ) = CONS( elem, Nil );
      end = CDR( end );
    }
  }
  va_end( va );

  return list;
}

void slow_dck( dexp d )
{
  FAST_DCK(d);

  if (d->type==dexp_array) {
    int i;
    for (i=0; i<d->v.array_v.size; ++i) {
      slow_dck( d->v.array_v.elems[i] );
    }
  } else if (d->type==dexp_tuple) {
    int i;
    for (i=0; i<d->v.tuple_v.size; ++i) {
      slow_dck( d->v.tuple_v.elems[i] );
    }
  } else if (d->type==dexp_map) {
    dexp key, value;
    hashiter hi;
    hash_init_iter( &hi, d->v.map_v );
    while (hash_iter_next( &hi, &key, &value )) {
      slow_dck( key );
      slow_dck( value );
    }
  } else if (d->type==dexp_cons) {
    int i;

    // Check the constructor
    A(d->v.cons_v.ctor);

    // Check the args
    A(d->v.cons_v.nargs>=0);
    for (i=0; i<d->v.cons_v.nargs; ++i) {
      slow_dck( d->v.cons_v.args[i] );
    }
  }
}

dexp _Nil( void )
{
  static dexp nil = 0;

  if (nil==0) {
    nil = mkcons( "Nil" );
  }
  return nil;
}

int dexp_equal( dexp d0, dexp d1 )
{
  int i;

  DCK(d0);
  DCK(d1);

  if (d0->type != d1->type) {
    EQUAL_PROFILE_NE();
    return 0;
  } else {
    switch( d0->type ) {
      case dexp_char:
        EQUAL_PROFILE(dexp_char);
        return d0->v.char_v == d1->v.char_v;
        break;
      case dexp_int:
        EQUAL_PROFILE(dexp_int);
        return d0->v.int_v == d1->v.int_v;
        break;
      case dexp_float:
        EQUAL_PROFILE(dexp_float);
        return d0->v.float_v == d1->v.float_v;
        break;
      case dexp_double:
        EQUAL_PROFILE(dexp_double);
        return d0->v.double_v == d1->v.double_v;
        break;
      case dexp_string:
        EQUAL_PROFILE(dexp_string);
        return !strcmp( d0->v.string_v, d1->v.string_v );
        break;
      case dexp_array:
        EQUAL_PROFILE(dexp_array);
        if (d0->v.array_v.size != d1->v.array_v.size) {
          return 0;
        }
        for (i=0; i<d0->v.array_v.size; ++i) {
          if (!dexp_equal( d0->v.array_v.elems[i], d1->v.array_v.elems[i] )) {
            return 0;
          }
        }
        return 1;
        break;
      case dexp_tuple:
        EQUAL_PROFILE(dexp_tuple);
        if (d0->v.tuple_v.size != d1->v.tuple_v.size) {
          return 0;
        }
        for (i=0; i<d0->v.tuple_v.size; ++i) {
          if (!dexp_equal( d0->v.tuple_v.elems[i], d1->v.tuple_v.elems[i] )) {
            return 0;
          }
        }
        return 1;
        break;
      case dexp_map:
        EQUAL_PROFILE(dexp_map);
        err(( "Not implemented.\n" ));
        break;
      case dexp_cons:
        EQUAL_PROFILE(dexp_cons);
        if (CONSCOUNT(d0) != CONSCOUNT(d1)) {
          return 0;
        }
        if (CONSCOUNT(d0)==0) {
          return d0==d1;
        }
        if (strcmp( d0->v.cons_v.ctor, d1->v.cons_v.ctor )) {
          return 0;
        }
        for (i=0; i<CONSCOUNT(d0); ++i) {
          if (!dexp_equal( CONSELEM( d0, i ), CONSELEM( d1, i ) )) {
            return 0;
          }
        }
        return 1;
        break;
      default:
        err(( "dexp_equal(): Bad dexp type %d\n", d0->type ));
        break;
    }
  }
  A(0);
  return 0;
}

static void append_onto( dexp m0, dexp m1 )
{
  DCK(m0);
  DCK(m1);
  A(ISMAP(m0));
  A(ISMAP(m1));

  hashiter hi;
  dexp key, value;
  hash_init_iter( &hi, m1->v.map_v );
  while (hash_iter_next( &hi, &key, &value )) {
    pM( m0, key, value );
  }
}

dexp dexp_append( dexp d0, dexp d1 )
{
  DCK(d0);
  DCK(d1);

  if (ISMAP(d0) && ISMAP(d1)) {
    dexp m = EMAP();
    append_onto( m, d0 );
    append_onto( m, d1 );
    return m;
  } else if (ISLIST(d0) && ISLIST(d1)) {
    CASE (d0) {
      match (K(Cons,_(a),_(d))) {
        return CONS( V(a), dexp_append( V(d), d1 ) );
      }
      match (Nil) {
        return d1;
      }
    } ENDCASE;
  } else if (ISARRAY(d0) && ISARRAY(d1)) {
    dexp a = AR( ARRAYSIZE(d0) + ARRAYSIZE(d1) );
    int i;
    for (i=0; i<ARRAYSIZE(d0); ++i) {
      pA( a, i, gA( d0, i ) );
    }
    for (i=0; i<ARRAYSIZE(d1); ++i) {
      pA( a, i+ARRAYSIZE(d0), gA( d1, i ) );
    }
    return a;
  } else if (ISTUPLE(d0) && ISTUPLE(d1)) {
    dexp a = AR( TUPLESIZE(d0) + TUPLESIZE(d1) );
    int i;
    for (i=0; i<TUPLESIZE(d0); ++i) {
      pA( a, i, gA( d0, i ) );
    }
    for (i=0; i<TUPLESIZE(d1); ++i) {
      pA( a, i+TUPLESIZE(d0), gA( d1, i ) );
    }
    return a;
  } else if (ISSTRING(d0) && ISSTRING(d1)) {
    A( dexp_strlen( d0 ) + dexp_strlen( d1 ) <= STRING_BUF_SIZE );
    strcpy( string_buf, gST( d0 ) );
    strcat( string_buf, gST( d1 ) );
    return mkstring(string_buf);
  } else if ((ISSTRING(d0) && ISCHAR(d1)) || (ISSTRING(d1) && ISCHAR(d0))) {
    dexp thechar = ISSTRING(d0) ? d1 : d0;
    dexp thestring = ISSTRING(d0) ? d0 : d1;
    return dexp_append( dexp_char2string( thechar ), thestring );
  } else if (ISSYMBOL(d0) && ISSYMBOL(d1)) {
    return mksymbol(
      gST( dexp_append( mkstring(CONSCTORS(d0)), mkstring(CONSCTORS(d1)) ) ) );
  } else {
    spew(( "Can't append.\n" ));
    dspew( d0 ); 
    dspew( d1 ); 
    err(( "" ));
  }
  A(0);
  return 0;
}

int dexp_list_length( dexp list )
{
  int length = 0;
  while (!EQUAL(list,Nil)) {
    length++;
    list = CDR(list);
  }
  return length;
}

dexp list2ctor( dexp ctor, dexp list )
{
  int nargs = dexp_list_length( list );

  if (nargs==0) {
    // Use canonical, for a symbol.
    return mksymbol( CONSCTORS(ctor) );
  } else {
    dexp ct = dexp_make_empty_cons( CONSCTORS(ctor), nargs );
    int i=0;
    while (!EQUAL(list,Nil)) {
      A(i>=0 && i<nargs);
      CONSELEM(ct,i) = CAR(list);
      list = CDR(list);
      i++;
    }
    return ct;
  }
}

dexp args2list( dexp ctor )
{
  int i;
  dexp list = Nil;

  DCK(ctor);
  A(ISCONS(ctor));

  for (i=CONSCOUNT(ctor)-1; i>=0; --i) {
    list = CONS( CONSELEM(ctor,i), list );
  }

  return list;
}

int dexp_strlen( dexp s0 )
{
  DCK(s0);
  A(ISSTRING(s0));
  return strlen( s0->v.string_v );
}

dexp dexp_char2string( dexp c )
{
  int bufsize = STRING_BUF_SIZE;
  DCK(c);
  A(ISCHAR(c));
  A(bufsize>=2);
  string_buf[0] = gC(c);
  string_buf[1] = 0;
  return mkstring(string_buf);
}

static dexp dexp_mapfun_list( dexp (*fun)( dexp ), dexp list )
{
  A(fun);
  A(ISLIST(list));

  CASE (list) {
    match (Nil) {
      return Nil;
    } else match (K(Cons,_(a),_(d))) {
      return K(Cons, (*fun)(V(a)), dexp_mapfun( fun, V(d) ));
    }
  } ENDCASE;
  A(0);
  return Nil;
}

static dexp dexp_mapfun_ctor( dexp (*fun)( dexp ), dexp ctor )
{
  int i;

  // If no args, then this has no effect, and besides,
  // no-arg ctors are symbols, and thus canonicalized.
  if (CONSCOUNT(ctor)==0) {
    return ctor;
  }

  dexp nctor = dexp_make_empty_cons( CONSCTORS(ctor), CONSCOUNT(ctor) );
  for (i=0; i<CONSCOUNT(ctor); ++i) {
    pK( nctor, i, (*fun)( gK( ctor, i ) ) );
  }
  return nctor;
}

static dexp dexp_mapfun_array( dexp (*fun)( dexp ), dexp array )
{
  int i;

  dexp narray = AR(ARRAYSIZE(array));

  for (i=0; i<ARRAYSIZE(array); ++i) {
    pA(narray,i,(*fun)( gA(array,i) ));
  }

  return narray;
}

static dexp dexp_mapfun_map( dexp (*fun)( dexp ), dexp map )
{
  int i;

  dexp nmap = EMAP();

  FORMAP (map,k,v) {
    dexp nk = (*fun)( k );
    dexp nv = (*fun)( v );
    pM( nmap, nk, nv );
  }

  return nmap;
}

static dexp dexp_mapfun_tuple( dexp (*fun)( dexp ), dexp tuple )
{
  int i;

  dexp ntuple = T(TUPLESIZE(tuple));

  for (i=0; i<TUPLESIZE(tuple); ++i) {
    pT(ntuple,i,(*fun)( gT(tuple,i) )); 
  }

  return ntuple;
}

dexp dexp_mapfun( dexp (*fun)( dexp ), dexp collection )
{
  A(fun);
  if (ISLIST(collection)) {
    return dexp_mapfun_list( fun, collection );
  } else if (ISCONS(collection)) {
    return dexp_mapfun_ctor( fun, collection );
  } else if (ISARRAY(collection)) {
    return dexp_mapfun_array( fun, collection );
  } else if (ISMAP(collection)) {
    return dexp_mapfun_map( fun, collection );
  } else if (ISTUPLE(collection)) {
    return dexp_mapfun_tuple( fun, collection );
  } else {
    dspew( collection );
    err(( "Can't mapfun that." ));
  }
  A(0);
  return Nil;
}

void dexp_check_string_len( char *s, int len )
{
  A(strlen(s)==len);
}

dexp dexp_string2symbol( dexp s )
{
  DCK(s);
  A(ISSTRING(s));
  return mksymbol( gST( s ) );
}

dexp dexp_char2symbol( dexp c )
{
  return dexp_string2symbol( dexp_char2string( c ) );
}

dexp dexp_symbol2string( dexp s )
{
  return mkstring( SYMSTRING( s ) );
}

dexp dexp_tostring( dexp d )
{
  if (ISSYMBOL(d)) {
    return mkstring( SYMSTRING( d ) );
  } else if (ISSTRING(d)) {
    return d;
  } else if (ISCHAR(d)) {
    return dexp_char2string( d );
  } else {
    dspew( d );
    err(( "Can't convert to symbol." ));
    return Nil;
  }
}

dexp dexp_tosymbol( dexp d )
{
  if (ISSYMBOL(d)) {
    return d;
  } else if (ISSTRING(d)) {
    return mksymbol( gST(d) );
  } else if (ISCHAR(d)) {
    return mksymbol( gST( dexp_tostring( d ) ) );
  } else {
    dspew( d );
    err(( "Can't convert to symbol." ));
    return Nil;
  }
}


dexp dexp_tointeger( dexp d )
{
  if (ISSYMBOL(d)) {
    int n;
    sscanf( SYMSTRING(d), "%d", &n );
    return I(n);
  } else if (ISINT(d)) {
    return d;
  } else {
    dspew( d );
    err(( "Can't convert to integer." ));
    return Nil;
  }
}

dexp dexp_tochar( dexp d )
{
  if (ISINT(d)) {
    int di = gI(d);
    if (di>=0 && di<=255) {
      return mkchar( (char)di );
    } else {
      err(( "Char %d out of range!", di ));
      return Nil;
    }
  } else if (ISCHAR(d)) {
    return d;
  } else {
    dspew( d );
    err(( "Can't convert to integer." ));
    return Nil;
  }
}

void dexp_report( void )
{
  int i, total=0;
  printf( "Allocation count:\n" );
  for (i=0; i<=dexp_max; ++i) {
    printf( "  %8s: %6d\n", dexp_typenames[i], mkcounts[i] );
    total += mkcounts[i];
  }
  printf( "  %8s: %6d\n", "*total", total );
}

char *typename( dexp d )
{
  DCK(d);
  return dexp_typenames[d->type];
}

void dexp_equal_profiling_report( void )
{
#if EQUAL_PROFILING
  int i, total=0;
  printf( "dexp_equal() calls:\n" );
  for (i=dexp_min; i<=dexp_max; ++i) {
    printf( "  %13s: %9d\n", dexp_typenames[i], equal_counts[i] );
    total += equal_counts[i];
  }
  printf( "  %13s: %9d\n", "unequal types", unequal_types );
  total += unequal_types;
  printf( "  %13s: %9d\n", "total", total );
#endif
}

dexp dexp_list2array( dexp list )
{
  int i=0;
  dexp ar = mkarray( dexp_list_length( list ) );
  FORLIST (list,e) {
    pA( ar, i, e );
    i++;
  }
  return ar;
}

dexp dexp_list2tuple( dexp list )
{
  int i=0;
  dexp ar = mktuple( dexp_list_length( list ) );
  FORLIST (list,e) {
    pT( ar, i, e );
    i++;
  }
  return ar;
}

// If this 'array' is an array of => operations,
// then it's really a map, so convert it.
static dexp dexp_array2map( dexp array )
{
  int i;

  // First, scan it
  FORARRAY (array,e) {
    CASE (e) {
      match (K(=>,_(key),_(value))) {
      } otherwise (dummy) {
        return 0;
      }
    } ENDCASE;
  }

  // Okay, it's really a map, so build it
  {
    dexp map = EMAP();
    FORARRAY (array,e) {
      CASE (e) {
        match (K((=>),_(key),_(value))) {
          pM( map, V(key), V(value) );
        } otherwise (dummy) {
          err(( "??" ));
        }
      } ENDCASE;
    }

    return map;
  }
}

dexp dexp_array2map_maybe( dexp array )
{
  dexp map = dexp_array2map( array );
  if (!map) {
    return array;
  } else {
    return map;
  }
}

dexp dexp_nth( dexp list, int n )
{
  A(n>=0);
  if (n==0) {
    return CAR(list);
  } else {
    return dexp_nth( CDR(list), n-1 );
  }
}

// replace \ with \\ in s
dexp dexp_escape( dexp s )
{
  int num_escapes=0, i, len;
  char *ss, *nss, *nssc;

  A(ISSTRING(s));

  ss = gST(s);
  len = strlen( ss );

  // First, count the number of backslashes
  for (i=0; i<len; ++i) {
    if (ss[i]=='\\' || ss[i]=='\"' || ss[i]=='\'') {
      num_escapes++;
    }
  }

  // Now, build a new string, replacing \ with \\, natch.
  nss = malik( strlen( ss ) + num_escapes );
  nssc = nss;
  for (i=0; i<len; ++i) {
    if (ss[i]=='\\' || ss[i]=='\"' || ss[i]=='\'') {
      *nssc++ = '\\';
    }
    *nssc++ = ss[i];
  }

  return mkstring( nss );
}

dexp dexp_keys( dexp map )
{
  dexp keys = Nil;
  DCK(map);
  A(ISMAP(map));
  FORMAP (map,k,v) {
    keys = CONS(k,keys);
  }
  return keys;
}

dexp dexp_reverse( dexp list )
{
  dexp rlist = Nil;
  while (!EQUAL(list,Nil)) {
    rlist = CONS(CAR(list),rlist);
    list = CDR(list);
  }
  return rlist;
}
