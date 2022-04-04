// $Id: pt.c,v 1.10 2005/03/01 16:12:57 greg Exp $

#include <stdio.h>
#include <string.h>
#include "io.h"
#include "mrd.h"
#include "pt.h"
#include "spew.h"

static int show = 0;

#define WS S(ws)

#define Bind(__nt,__exp) K(exp_statement, K((=),(__nt),(__exp)))
//#define Bind(__nt,__exp) K(Bind, (__nt), (__exp))

static dexp orlist( dexp list )
{
  A(dexp_list_length( list )>0);

  if (dexp_list_length( list )==1) {
    return CAR(list);
  } else {
    return orlist( CONS( K((|),CAR(list),CADR(list)), CDDR(list) ) );
  }
}

dexp pt_get_bootstrap_grammar( void )
{
  return
  K( block_statement,
    L(
      Bind( S(top_statement), K( top_statement, WS, S(statement), WS ) ),

      Bind( S(operator),
        K((|),
          K( ai, S(opchar), S(operator) ),
          K( ain, S(opchar) ) ) ),

      Bind( S(opchar),
        orlist(
          L(
            C(!),
            K((..),C(#),C(&)),
            K((..),C(*),C(+)),
            K((..),C(-),C(/)),
            C(:),
            K((..),C(<),C(@)),
            C(\\),
            K((..),C(^),C(`)),
            C(|),
            C(~) )) ),

      Bind( WS,
        K((|),
          K( ai, S(wschar), WS ),
          K( Nothing, S(ainn) ) ) ),
      Bind( S(wschar),
        orlist(
          L(
            mkchar(' '),
            C(\t),
            C(\n) ) ) ),

      Bind( S(ident),
        K((|),
          S(regular_ident),
          S(opname) ) ),
      Bind( S(regular_ident),
        K((|),
          K( ai, S(idchar), S(regular_ident) ),
          K( ain, S(idchar) ) ) ),
      Bind( S(idchar),
        orlist(
          L(
            K((..),C(a),C(z)),
            K((..),C(A),C(Z)),
            K((..),C(0),C(9)),
            C(_) ) ) ),
      Bind( S(opname),
        K( opname,
          mkchar('('),
          S(operator),
          mkchar(')') ) ),

      Bind( S(exp),
        K((|),
          K(opexp,S(baseexp),WS,S(operator),WS,S(exp)),
          S(baseexp)) ),
      Bind( S(pexp),
        K(pexp,mkchar('('),WS,S(exp),WS,mkchar(')')) ),
      Bind( S(baseexp),  
        orlist(
          L(
            S(construction),
            S(array),
            S(pexp),
            S(tuple),
            S(list),
            S(float),
            S(integer),
            S(ident),
            S(literal) ) ) ),

      Bind( S(construction),
        K(construction,
          S(ident),
          WS,
          mkchar('('),
          WS,
          S(explist),
          WS,
          mkchar(')') ) ),
      Bind( S(list),
        K(list,
          mkchar('['),
          WS,
          S(explist),
          WS,
          mkchar(']') ) ),
      Bind( S(array),
        K(array,
          mkchar('{'),
          WS,
          S(explist),
          WS,
          mkchar('}') ) ),
      Bind( S(tuple),
        K(tuple,
          mkchar('('),
          WS,
          S(explist),
          WS,
          mkchar(')') ) ),

      Bind( S(explist),
        orlist(
          L(
            K( el,
              S(exp),
              WS,
              mkchar(','),
              WS,
              S(explist) ),
            K( ellast, S(exp) ),
            K( Nothing, S(eln) ) ) ) ),

      Bind( S(integer),
        orlist( L( S(hex_integer), S(octal_integer), S(decimal_integer) ) ) ),

      Bind( S(octal_integer), K(octal_integer,C(0),C(o),S(oclist)) ),
      Bind( S(decimal_integer),
        orlist(
          L(
            K(decimal_integer_explicit,C(0),C(d),S(dclist)),
            K(decimal_integer,S(dclist)) ) ) ),
      Bind( S(hex_integer), K(hex_integer,C(0),C(x),S(hclist)) ),

      Bind( S(octalchar), K((..),C(0),C(7)) ),
      Bind( S(decimalchar), K((..),C(0),C(9)) ),
      Bind( S(hexchar),
        orlist(
          L(
            K((..),C(0),C(9)),
            K((..),C(a),C(f)),
            K((..),C(A),C(F)) ) ) ),

      Bind( S(dclist),
        K((|),
          K( ai, S(decimalchar), S(dclist) ),
          K( ain, S(decimalchar) )) ),
      Bind( S(hclist),
        K((|),
          K( ai, S(hexchar), S(hclist) ),
          K( ain, S(hexchar) )) ),
      Bind( S(oclist),
        K((|),
          K( ai, S(octalchar), S(oclist) ),
          K( ain, S(octalchar) )) ),

      Bind( S(float),
        K(floatparts,
          S(dclist),
          C(.),
          S(dclist) ) ),

      Bind( S(exp_statement),
        K( exp_statement, S(exp), WS, C(;) ) ),
      Bind( S(block_statement),
        K( block_statement,
          mkchar('{'),
          WS,
          S(statement_list),
          WS,
          mkchar('}') ) ),
      Bind( S(statement_list),
        K((|),
          K( sl, S(statement), WS, S(statement_list) ),
          K( Nothing, S(sln) )) ),
      Bind( S(statement),
        K((|),
          S(exp_statement),
          S(block_statement)) ),

      Bind( S(escaped_char),
        orlist(
          L(
            K(EChar,ST(\\t)),
            K(EChar,ST(\\\\)),
            K(EChar,mkstring("\\\"")),
            K(EChar,mkstring("\\\'")),
            K(EChar,ST(\\n)) ) ) ),

      Bind( S(numeric_char),
        orlist(
          L(
            S(octal_numeric_char),
            S(decimal_numeric_char),
            S(hex_numeric_char) ) ) ),
            
      Bind( S(octal_numeric_char),
        K( octal_numeric_char,
          C(\\),
          C(o),
          S(oclist) ) ),

      Bind( S(decimal_numeric_char),
        K( decimal_numeric_char,
          C(\\),
          C(d),
          S(dclist) ) ),

      Bind( S(hex_numeric_char),
        K( hex_numeric_char,
          C(\\),
          C(x),
          S(hclist) ) ),

      Bind( S(other_than_double_quote),
        K((|),
          K((..),mkchar('\x00'),mkchar('\"'-1)),
          K((..),mkchar('\"'+1),mkchar('\x7f'))) ),

      Bind( S(other_than_single_quote),
        K((|),
          K((..),mkchar('\x00'),mkchar('\''-1)),
          K((..),mkchar('\''+1),mkchar('\x7f'))) ),

      Bind( S(double_quote_char),
        orlist(
          L(
            S(escaped_char),
            S(numeric_char),
            S(other_than_double_quote) ) ) ),
      Bind( S(single_quote_char),
        orlist(
          L(
            S(escaped_char),
            S(numeric_char),
            S(other_than_single_quote) ) ) ),

      Bind( S(literal),
        K((|),
          S(char_literal),
          S(string_literal)) ),
      Bind( S(char_literal),
        K( char_literal,
          mkchar('\''),
          S(single_quote_char),
          mkchar('\'') ) ),

      Bind( S(string_literal),
        K( string_literal,
          mkchar('\"'),
          S(stringchars),
          mkchar('\"') ) ),
      Bind( S(stringchars),
        K((|),
          K( ai, S(double_quote_char), S(stringchars) ),
          K( ain, S(double_quote_char) )) )
      ) );
}

dexp pt_clean( dexp parsed )
{
  CASE (parsed) {
    match (K(ai,_(c),_(rest))) {
      return dexp_append( dexp_tosymbol( pt_clean(V(c)) ), pt_clean( V(rest) ) );
    } else match (K(ain,_(c))) {
      return dexp_char2symbol( pt_clean( V(c) ) );
    } else match (S(ainn)) {
      return dexp_string2symbol( mkstring("") );
    } else match (K(String,_(s))) {
      //return dexp_string2symbol( V(s) );
      return V(s);
    } else match (K(EChar,_(s))) {
      char *s = gST(pt_clean(V(s)));
      char c=0;
      if (!strcmp(s,"\\n")) {
        c = '\n';
      } else if (!strcmp(s,"\\t")) {
        c = '\t';
      } else if (!strcmp(s,"\\\"")) {
        c = '\"';
      } else if (!strcmp(s,"\\\'")) {
        c = '\'';
      } else if (!strcmp(s,"\\\\")) {
        c = '\\';
      } else {
        err(( "Bad escape char \"%s\"", s ));
      }
      return mkchar( c );
    } else match (K(a,_(c))) {
      return dexp_char2string( pt_clean( V(c) ) );
    } else match (K(Char,_(c))) {
      return V(c);
    } else match (K(construction,_(ident),_(ws),_(lparen),
                    _(ws),_(list),_(ws),_(rparen))) {
      return list2ctor( pt_clean( V(ident) ), pt_clean( V(list) ) );
    } else match (Nil) {
      return Nil;
    } else match (K(ellast,_(exp))) {
      return L( pt_clean( V(exp) ) );
    } else match (K(el,_(exp0),_(ws),_(comma),_(ws),_(exp1))) {
      return CONS( pt_clean( V(exp0) ), pt_clean( V(exp1) ) );
    } else match (K(Nothing,S(eln))) {
      return Nil;
    } else match (S(eln)) {
      return Nil;
    } else match (K(pexp,_(lparen),_(ws),_(exp),_(ws),_(rparen))) {
      return K(pexp,pt_clean(V(exp)));
    } else match (K(opexp,_(lexp),_(ws),_(op),_(ws),_(rexp))) {
      dexp op =
        dexp_append( dexp_char2symbol( mkchar( '(' ) ),
          dexp_append( pt_clean( V(op) ), dexp_char2symbol( mkchar( ')' ) ) ) );
      return K( opexp, op, pt_clean( V(lexp) ), pt_clean( V(rexp) ) );
    } else match (K(top_statement,_(ws),_(tree),_(ws))) {
      return pt_clean( V(tree) );
    } else match (K(list,_(dummy),_(dummy),_(el),_(dummy),_(dummy))) {
      return pt_clean( V(el) );
    } else match (K(array,_(dummy),_(dummy),_(el),_(dummy),_(dummy))) {
      dexp array = dexp_list2array( pt_clean( V(el) ) );
      array = dexp_array2map_maybe( array );
      return array;
    } else match (K(tuple,_(dummy),_(dummy),_(el),_(dummy),_(dummy))) {
      return dexp_list2tuple( pt_clean( V(el) ) );
    } else match (K(octal_integer,_(_),_(_),_(isym))) {
      int i, r;
      r = sscanf( SYMSTRING( pt_clean( V(isym) ) ), "%o", &i );
      A(r==1);
      return mkint(i);
    } else match (K(decimal_integer,_(isym))) {
      int i, r;
      r = sscanf( SYMSTRING( pt_clean( V(isym) ) ), "%d", &i );
      A(r==1);
      return mkint(i);
    } else match (K(decimal_integer_explicit,_(_),_(_),_(isym))) {
      int i, r;
      r = sscanf( SYMSTRING( pt_clean( V(isym) ) ), "%d", &i );
      A(r==1);
      return mkint(i);
    } else match (K(hex_integer,_(zero),_(x),_(isym))) {
      int i, r;
      r = sscanf( SYMSTRING( pt_clean( V(isym) ) ), "%x", &i );
      A(r==1);
      return mkint(i);
    } else match (K(octal_numeric_char,_(_),_(_),_(oclist))) {
      int n;
      sscanf( SYMSTRING( pt_clean( V(oclist) ) ), "%o", &n );
      return dexp_tochar( I(n) );
    } else match (K(decimal_numeric_char,_(_),_(_),_(dclist))) {
      return dexp_tochar( dexp_tointeger( pt_clean( V(dclist) ) ) );
    } else match (K(hex_numeric_char,_(_),_(_),_(hclist))) {
      int n;
      sscanf( SYMSTRING( pt_clean( V(hclist) ) ), "%x", &n );
      return dexp_tochar( I(n) );
    } else match (K(octal_integer,_(zero),_(isym))) {
      int i, r;
      r = sscanf( SYMSTRING( pt_clean( V(isym) ) ), "%o", &i );
      A(r==1);
      return mkint(i);
    } else match (K(floatparts,_(ipart),_(dummy),_(fracpart))) {
      int r;
      float f;
      dexp all =
        dexp_append( pt_clean( V(ipart) ),
          dexp_append( S(.), pt_clean( V(fracpart) ) ) );
      r = sscanf( SYMSTRING( all ), "%f", &f );
      A(r==1);
      return mkfloat(f);
    } else match (K(exp_statement,_(exp),_(ws),_(semicolon))) {
      return K(exp_statement,pt_clean(V(exp)));
    } else match (K(block_statement,_(_),_(_),_(sl),_(_),_(_))) {
      return K(block_statement,pt_clean( V(sl) ));
    } else match (K(sl,_(car),_(_),_(cdr))) {
      return CONS( pt_clean( V(car) ), pt_clean( V(cdr) ) );
    } else match (S(sln)) {
      return Nil;
    } else match (K(Nothing,S(sln))) {
      return Nil;
    } else match (K(char_literal,_(_),_(c),_(_))) {
      return pt_clean( V(c) );
    } else match (K(string_literal,_(_),_(s),_(_))) {
      return dexp_symbol2string( pt_clean( V(s) ) );
    } else match (K(opname,_(l),_(op),_(r))) {
      return dexp_append(
        dexp_char2symbol( pt_clean( V(l) ) ),
        dexp_append(
          pt_clean( V(op) ),
          dexp_char2symbol( pt_clean( V(r) ) ) ) );
    } else match (K(lambda,_(_),_(_),_(_),_(_),
                   _(params),_(_),_(_),_(_),_(body))) {
      return K(lambda,pt_clean(V(params)),pt_clean(V(body)));
    } else match (K(formal_param,_(fp))) {
      return pt_clean( V(fp) );
    }
  } ENDCASE;
  A(0);
  return Nil;
}

/*

flatten_oplists() and unflatten_oplists() seem to be inverses, but
they aren't, really.  Flattening removes the tree structure imposed
arbitrarily by the parser, while unflattening imposes a new tree
structure based on operator precedence.

Note that the flattening operation flattens opexp nodes, but ignores
pexp nodes.  pexp nodes represent parenthesized expressions, whose
contents are not subject to precedence rearrangements (i.e. the whole
point of a parenthesized expression).

*/

// opexp( (*), opexp((+),a,b), opexp((+),c,d) ) =>
// oplist( [ a, (+), b, (*), c, (+), d ] )
static dexp flatten_oplists( dexp tree );

static dexp flatten_oplist( dexp tree )
{
  CASE (tree) {
    match (K(opexp,_(op),_(left),_(right))) {
      return
        dexp_append(
          flatten_oplist( V(left) ),
          dexp_append(
            L( V(op) ),
            flatten_oplist( V(right) ) ) );
    } otherwise (t) {
      return L( flatten_oplists( V(t) ) );
    }
  } ENDCASE;
  A(0);
  return Nil;
}

static dexp flatten_oplists( dexp tree )
{
  CASE (tree) {
    match (K(opexp,_(op),_(left),_(right))) {
      return K( oplist, flatten_oplist( tree ) );
    } otherwise (t) {
      if (ISAGG(V(t))) {
        return dexp_mapfun( &flatten_oplists, V(t) );
      } else {
        return V(t);
      }
    }
  } ENDCASE;
  A(0);
  return Nil;
}

#define MS mkstring
#define DEFAULT_PREC (6)
static dexp raw_precedence_table( void )
{
  return L(
    L( MS( "->" ), MS( "." ) ),
    L( MS( "!" ), MS( "~" ), MS( "++" ), MS( "--" ), MS( "-" ) ),
    L( MS( "*" ), MS( "/" ), MS( "%" ) ),
    L( MS( "+" ), MS( "-" ) ),
    L( MS( "<<" ), MS( ">>" ), MS( "<<<" ), MS( ">>>" ) ),
    L( MS( "<" ), MS( "<=" ), MS( ">" ), MS( ">=" ) ),
    L( MS( "==" ), MS( "!=" ) ),
    L( MS( "&" ) ),
    L( MS( "^" ) ),
    L( MS( "|" ) ),
    L( MS( "&&" ) ),
    L( MS( "||" ) ),
    L(
      MS( "=" ), MS( "*=" ), MS( "/=" ), MS( "%=" ), MS( "+=" ),
      MS( "-=" ), MS( "<<=" ), MS( ">>=" ), MS( "<<<=" ), MS( ">>>=" ),
      MS( "&=" ), MS( "^=" ), MS( "|=" ), MS( "&&=" ), MS( "||=" ) ) );
}

static dexp prec_table_prepare( dexp pt )
{
  int level = 0;

  dexp table = EMAP();

  while (1) {
    A(ISLIST(pt));

    if (ISPAIR(pt)) {
      FORLIST (CAR(pt),op) {
        op = dexp_string2symbol(
          dexp_append( mkstring( "(" ),
            dexp_append( op, mkstring( ")" ) ) ) );
        pM( table, op, I(level) );
      }
    } else {
      break;
    }

    pt = CDR(pt);
    level++;
  }

  return table;
}

static dexp get_precedence_table( void )
{
  static dexp pt = 0;

  if (!pt) {
    pt = prec_table_prepare( raw_precedence_table() );
  }

  return pt;
}

static int precedence( dexp op )
{
  dexp pt = get_precedence_table();
  dexp prec = gM( pt, op );
  if (!prec) {
    return DEFAULT_PREC;
  } else {
    return gI( prec );
  }
}

// oplist( [ a, (+), b, (*), c, (+), d ] ) =>
// opexp( (+), a, opexp( (+), opexp((*),b,c), d ) )
// It also does pexp( a ) => a, since pexp is no
// longer needed.
static dexp unflatten_oplist( dexp list );

static dexp unflatten_oplists( dexp tree )
{
  CASE (tree) {
    match (K(oplist,_(list))) {
      return unflatten_oplist( V(list) );
    } else match (K(pexp,_(e))) {
      return unflatten_oplists( V(e) );
    } otherwise (t) {
      if (ISAGG(V(t))) {
        return dexp_mapfun( &unflatten_oplists, V(t) );
      } else {
        return V(t);
      }
    }
  } ENDCASE;
  A(0);
  return Nil;
}

static dexp unflatten_oplist1( dexp list );

static dexp unflatten_oplist( dexp list )
{
  while (dexp_list_length( list )!=1) {
    A(dexp_list_length( list )>1);
    list = unflatten_oplist1( list );
  }

  A(dexp_list_length( list )==1);

  return gL(list,0);
}

static dexp unflatten_oplist1( dexp list )
{
  CASE (list) {
    match (K(Cons,_(a),
             K(Cons,_(op0),
               K(Cons,_(b),
                 K(Cons,_(op1),
                   K(Cons,_(c),_(rest))))))) {
      dexp a = V(a);
      dexp b = V(b);
      dexp c = V(c);

      if (precedence( V(op0) ) <= precedence( V(op1) )) {
        a = unflatten_oplists( a );
        b = unflatten_oplists( b );
        return
          K(Cons,
            mkcons(SYMSTRING(V(op0)),a,b),
            K(Cons,V(op1),K(Cons,c,V(rest))));
      } else {
        return
          K(Cons,
            a,
            K(Cons,
              V(op0),
              unflatten_oplist1(
                K(Cons,
                  b,
                  K(Cons,
                    V(op1),
                    K(Cons,c,V(rest)))))));
      }
    } else match (K(Cons,_(a),
                    K(Cons,_(op0),
                      K(Cons,_(b),Nil)))) {
      dexp a = V(a);
      dexp b = V(b);
      a = unflatten_oplists( a );
      b = unflatten_oplists( b );
      return L(mkcons(SYMSTRING(V(op0)),a,b));
    }
  } ENDCASE;
  A(0);
  return Nil;
}

static dexp operator_precedence( dexp tree )
{
  tree = flatten_oplists( tree );
  tree = unflatten_oplists( tree );
  return tree;
}

dexp pt_postprocess( dexp tree )
{
  tree = operator_precedence( tree );
  return tree;
}

static dexp finish( dexp parse_output )
{
  CASE (parse_output) {
    match (K(Ok,_(tree))) {
      return pt_postprocess( pt_clean( V(tree) ) );
    } else match (K(Bad,_(why))) {
      dspew( V(why) );
      err(( "Can't parse." ));
    }
  } ENDCASE;
  A(0);
  return Nil;
}

dexp pt_get_grammar( void )
{
  static dexp grammar;

  if (grammar) {
    return grammar;
  }

  dexp bootstrap = pt_get_bootstrap_grammar();
  bootstrap = mrd_cook( bootstrap );

  dexp basefile = io_read_file( "basegrammar.k" );
  dexp restfile = io_read_file( "grammar.k" );

  dexp base = finish( mrd_parse( bootstrap, S(top_statement), basefile ) );
  dexp therest = finish( mrd_parse( bootstrap, S(top_statement), restfile ) );
  base = mrd_cook( base );
  therest = mrd_cook( therest );

  grammar = mrd_merge( base, therest );

  return grammar;
}

dexp pt_parse( dexp input )
{
  dexp grammar = pt_get_grammar();
  dexp results;

  mrd_show( show );

  results = finish( mrd_parse( grammar, S(top_statement), input ) );

  mrd_show( 0 );

  return results;
}

dexp pt_parse_file( char *filename )
{
  return pt_parse( io_read_file( filename ) );
}

void pt_self_host_test( void )
{
  dexp grammar_text = io_read_file( "basegrammar.k" );
  dexp bootstrap, bootstrap_c, first, first_c, second;

  bootstrap = pt_get_bootstrap_grammar();
  bootstrap_c = mrd_cook( bootstrap );

  first = finish( mrd_parse( bootstrap_c, S(top_statement), grammar_text ) );
  first_c = mrd_cook( first );

  second = finish( mrd_parse( first_c, S(top_statement), grammar_text ) );

  spew(( "%d %d\n", EQUAL(bootstrap,first), EQUAL(first,second) ));
}

void pt_show( int onp )
{
  show = onp;
}
