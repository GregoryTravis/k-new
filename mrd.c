/* $Id: mrd.c,v 1.10 2005/03/01 16:14:20 greg Exp $ */

#include <stdio.h>
#include <string.h>
#include "dexp.h"
#include "io.h"
#include "mem.h"
#include "mrd.h"
#include "match.h"
#include "outline.h"

static int show=0;
static int serial=0;

static dexp mrd_cook_exp( dexp rhs )
{
  CASE (rhs) {
    match (K((|),_(a),_(b))) {
      dexp a = mrd_cook_exp( V(a) );
      dexp b = mrd_cook_exp( V(b) );
      return K(Or,a,b);
//    } else match (K(Chars,_(c0),_(c1))) {
//      return rhs;
    } else match (K((..),_(c0),_(c1))) {
      return rhs;
    } else match (K(Nothing,_(ct))) {
      return rhs;
    } else match (S(Dot)) {
      return rhs;
    } else match (K(String,_(s))) {
      return rhs;
    } otherwise (o) {
      if (ISCHAR(V(o))) {
        return K((..),V(o),V(o));
      } else if (ISSYMBOL(V(o))) {
        return K(NT,V(o));
      } else if (ISCONS(V(o))) {
        return K(Seq,CONSCTOR(V(o)),
          dexp_mapfun( mrd_cook_exp, args2list(V(o)) ));
      } else if (ISSTRING(V(o))) {
        return K(String,V(o));
      } else {
        dspew( V(o) );
        err(( "Oops" ));
      }
    }
  } ENDCASE;
  A(0);
  return Nil;
}

dexp mrd_cook( dexp raw )
{
  dexp m = EMAP();

  CASE (raw) {
    match (K(block_statement,_(bindings))) {
      FORLIST( V(bindings), lel ) {
        CASE (lel) {
//          match (K(Bind,_(nt),_(rhs))) {
          match (K(exp_statement,K((=),_(nt),_(rhs)))) {
            dexp crhs = mrd_cook_exp( V(rhs) );
            dexp bindlist = gM(m,V(nt));
            if (bindlist) {
              pM(m,V(nt),K(Or,crhs,bindlist));
            } else {
              pM(m,V(nt),crhs);
            }
/*
            if (!bindlist) {
              bindlist = Nil;
            }
            CASE (bindlist) {
              match (Nil) {
                pM(m,V(nt),K(Or,L(crhs)));
              } else match (K(Or,_(list))) {
                pM(m,V(nt),K(Or,CONS(crhs,V(list))));
              }
            } ENDCASE;
*/
          }
        } ENDCASE;
      }
    }
  } ENDCASE;

  return m;
}

// Merge two grammars; or, extend grammar a by grammar b.
dexp mrd_merge( dexp a, dexp b )
{
  dexp nterms;
  dexp merged = EMAP();

  nterms = dexp_append( dexp_keys( a ), dexp_keys( b ) );
  FORLIST (nterms,nterm) {
//printf( "merging----\n" );
//dspew( nterm );
    dexp aprod = gM(a,nterm);
    dexp bprod = gM(b,nterm);
    if (aprod && bprod) {
      pM(merged,nterm,K(Or,bprod,aprod));
    } else if (aprod) {
      pM(merged,nterm,aprod);
    } else if (bprod) {
      pM(merged,nterm,bprod);
    } else {
      // Do nothing
    }
  }
  return merged;
}

void mrd_show( int onp )
{
  show = onp;
}

dexp charize_strings( dexp e )
{
  if (ISMAP(e)) {
    dexp ne = EMAP();
    FORMAP (e,k,v) {
      pM(ne,k,charize_strings(v));
    }
    return ne;
  }

  CASE (e) {
    match (K(Or,_(a),_(b))) {
      return K(Or,charize_strings(V(a)),charize_strings(V(b)));
    } else match (K(Seq,_(ctor),_(a),_(b))) {
      return K(Seq,V(ctor),charize_strings(V(a)),charize_strings(V(b)));
    } else match (K(String,_(s))) {
      char *s = gST(V(s));
      if (strlen(s)==0) {
        return K(Nothing,S(string_end));
      } else {
        return
          K(Seq,
            S(string_node),
            K((..),mkchar(*s),mkchar(*s)),
            charize_strings( K(String,mkstring(s+1)) ) );
      }
    } else match (K(Nothing,_(what))) {
      return e;
    } else match (K(NT,_(nt))) {
      return e;
    } else match (K((..),_(a),_(b))) {
      return e;
    }
  } ENDCASE;
  NORETURN;
}

dexp binarize_seqs( dexp grammar )
{
  if (ISMAP(grammar)) {
    dexp ngrammar = EMAP();
    FORMAP (grammar,k,v) {
      pM(ngrammar,k,binarize_seqs(v));
    }
    return ngrammar;
  }

  CASE (grammar) {
    match (K(Or,_(a),_(b))) {
      return K(Or,binarize_seqs(V(a)),binarize_seqs(V(b)));
    } else match (K(Seq,_(ctor),_(list))) {
      if (ISPAIR(V(list))) {
        return K(Seq,V(ctor),
          binarize_seqs(CAR(V(list))),
          binarize_seqs(K(Seq,S(b_s),CDR(V(list)))));
      } else {
        return K(Nothing,S(list_end));
      }
    } otherwise (_) {
      return grammar;
    }
  } ENDCASE;
  NORETURN;
}

typedef enum ge_type
{
  ge_or=1,
  ge_seq,
  ge_nt,
  ge_chars,
  ge_nothing
} ge_type ;

typedef struct ge
{
  ge_type type;
  dexp orig;
  union {
   struct {
     int left, right;
   } or_v;
   struct {
     dexp ctor;
     int first, second;
   } seq_v;
   struct {
     int val;
   } nt_v;
   struct {
     int lo, hi;
   } chars_v;
   struct {
     dexp what;
   } nothing_v;
  } v;
} ge;

typedef enum ans_okbad
{
  a_none=0,
  a_ok=1,
  a_bad=2
} ans_okbad ;

typedef struct ans
{
  ans_okbad okbad;
  int newi;
  dexp tree;
} ans ;

char *g_input;
int g_inputsize;
ge *g_exps;
int g_nexps;
ans *g_memos;

ans iplub1( int e, int i, int phase )
{
  int s = serial++;

  A(i>=0 && i<=g_inputsize);
  A(e>=0 && e<g_nexps);
  int mi = e*(g_inputsize+1)+i;
  ans answer;
  answer.okbad = a_none;
  answer.newi = -1;
  answer.tree = 0;


  if (show) {
    if ((s%10000)==0) { spew(( "Step %d\n", s )); }
    spew(( "call %d at i %d ", s, i ));
    lspew( "st", g_exps[e].orig );
  }

  if (g_memos[mi].okbad != a_none &&
    (phase==0 || g_memos[mi].okbad==a_bad)) {
    //spew(( "MEMO GET mi %d e %d i %d s %d\n", mi, e, i, s ));
    if (show) { spew(( "  MEMO HIT\n" )); }
    answer = g_memos[mi];
  } else {
    ge *exp = &g_exps[e];
    A(exp);
    switch (exp->type) {
    case ge_or:
      {
        ans ans0 = iplub1( exp->v.or_v.left, i, phase );
        A(ans0.okbad != a_none);
        if (ans0.okbad==a_ok) {
          answer = ans0;
        } else {
          ans ans1 = iplub1( exp->v.or_v.right, i, phase );
          A(ans1.okbad != a_none);
          answer = ans1;
        }
      }
      break;
    case ge_seq:
      {
        ans ans0 = iplub1( exp->v.seq_v.first, i, phase );
        A(ans0.okbad != a_none);
        if (ans0.okbad==a_ok) {
          ans ans1 = iplub1( exp->v.seq_v.second, ans0.newi, phase );
          A(ans1.okbad != a_none);
          if (ans1.okbad == a_ok) {
            answer.okbad = a_ok;
            answer.newi = ans1.newi;
            if (phase==1) {
              answer.tree =
                mkcons( SYMSTRING(exp->v.seq_v.ctor),
                  ans0.tree, ans1.tree );
            }
          } else {
            answer = ans1;
          }
        } else {
          answer = ans0;
        }
      }
      break;
    case ge_nt:
      {
        answer = iplub1( exp->v.nt_v.val, i, phase );
      }
      break;
    case ge_chars:
      {
        char c = g_input[i];
        if (i<g_inputsize && (c>=exp->v.chars_v.lo && c<=exp->v.chars_v.hi)) {
          if (show) {
            spew(( "Chars(%c,%c) %c YES\n",
                   exp->v.chars_v.lo, exp->v.chars_v.hi, c ));
          }
          answer.okbad = a_ok;
          answer.newi = i+1;
          if (phase==1) {
            answer.tree = K(Char,mkchar(g_input[i]));
          }
        } else {
          if (show) {
            spew(( "Chars(%c,%c) %c NO\n",
                   exp->v.chars_v.lo, exp->v.chars_v.hi, c ));
          }
          answer.okbad = a_bad;
          if (phase==1) {
            answer.tree = K(badc,
              mkchar(exp->v.chars_v.lo),
              mkchar(exp->v.chars_v.hi),
              mkchar(c));
          }
        }
      }
      break;
    case ge_nothing:
      answer.okbad = a_ok;
      answer.newi = i;
      if (phase==1) {
        //answer.tree = K(Nothing,S(eln));
        //answer.tree = Nil;
        //answer.tree = exp->orig;
//        answer.tree = K(Nothing,exp->v.nothing_v.what);
answer.tree = exp->v.nothing_v.what;
      }
      break;
      
    default:
      err(( "Shit.\n" ));
      break;
    }

    // put in memo.
    g_memos[mi] = answer;
    //spew(( "MEMO SET mi %d e %d i %d s %d\n", mi, e, i, s ));
  }

  if (show) {
    spew(( "-> s %d i %d ans okbad %s newi %d ", s, i,
           (answer.okbad==a_ok?"ok":"bad"), answer.newi ));
    if (phase==1) {
      sldspew( answer.tree );
    }
    spew(( "\n" ));
  }

  return answer;
}

dexp iplub( dexp input, dexp grammar, dexp e, int i, dexp memos )
{
  int inputlen = ARRAYSIZE(input);
  char *ninput = NEWC(char,inputlen);
  int k;
  for (k=0; k<inputlen; ++k) {
    ninput[k] = gC(gA(input,k));
  }

  dexp gecodes = EMAP();
  dexp explist = Nil;
  int geserial=0;
  FORMAP (grammar,nt,exp) {
    explist = CONS( K(NT,nt), explist );
  }
  while (!EQUAL(explist,Nil)) {
    dexp exp = CAR(explist);
    explist = CDR(explist);
    dexp gec = gM(gecodes,exp);
    if (!gec) {
      int geci = geserial++;
      pM(gecodes,exp,I(geci));

      CASE (exp) {
        match (K(Or,_(a),_(b))) {
          explist = CONS( V(a), explist );
          explist = CONS( V(b), explist );
        } else match (K(Seq,_(ctor),_(a),_(b))) {
          explist = CONS( V(a), explist );
          explist = CONS( V(b), explist );
        } else match (K((..),_(lo),_(hi))) {
        } else match (K(Nothing,_(what))) {
        } else match (K(NT,_(nt))) {
          explist = CONS( gM(grammar,V(nt)), explist );
        }
      } ENDCASE;
    }
  }
  int num_codes = MAPSIZE(gecodes);
  ge *ges = NEWC(ge,num_codes);
  {
    FORMAP (gecodes,exp,gecode) {
      int gei = gI(gecode);
      ge *g = &ges[gei];

      g->orig = exp;

      CASE (exp) {
        match (K(Or,_(a),_(b))) {
          g->type = ge_or;
          g->v.or_v.left = gI(gM(gecodes,V(a)));
          g->v.or_v.right = gI(gM(gecodes,V(b)));
        } else match (K(Seq,_(ctor),_(a),_(b))) {
          g->type = ge_seq;
          g->v.seq_v.ctor = V(ctor);
          g->v.seq_v.first = gI(gM(gecodes,V(a)));
          g->v.seq_v.second = gI(gM(gecodes,V(b)));
        } else match (K((..),_(lo),_(hi))) {
          g->type = ge_chars;
          g->v.chars_v.lo = gC(V(lo));
          g->v.chars_v.hi = gC(V(hi));
        } else match (K(Nothing,_(what))) {
          g->type = ge_nothing;
          g->v.nothing_v.what = V(what);
        } else match (K(NT,_(nt))) {
          g->type = ge_nt;
          g->v.nt_v.val = gI(gM(gecodes,gM(grammar,V(nt))));
          explist = CONS( gM(grammar,V(nt)), explist );
        }
      } ENDCASE;
    }
  }

  int first = gI(gM(gecodes,K(NT,S(top_statement))));

  // memo index is gecode*inputsize+i
  ans *nmemos = NEWC(ans,num_codes*(inputlen+1));

  g_input = ninput;
  g_inputsize = inputlen;
  g_exps = ges;
  g_nexps = num_codes;
  g_memos = nmemos;

  serial = 0;
  iplub1( first, 0, 0 );

  serial = 0;
  ans answer = iplub1( first, 0, 1 );

  if (answer.okbad==a_ok) {
    return K(Ok,answer.tree,I(answer.newi));
  } else {
    return S(Bad);
  }
}

// phase=0 means full memo usage, and don't construct answer.
// phase=1 means ignore memo positives, and construct answer.
dexp plub( dexp input, dexp grammar, dexp e, int i, int phase, dexp memos )
{
  int s = serial++;
  dexp answer = 0;

  if ((s%10000)==0) { spew(( "Step %d\n", s )); }

  if (show) {
    spew(( "-> %5d ", s, i ));
    sldspew( e );
    spew(( "\n" ));
  }

  // Check memos
  dexp key = K(key,e,I(i));
  dexp value = gM(memos,key);
  if (value && (phase==0 || !ISCTOR(value,"Ok"))) {
    answer = value;
  } else {
    CASE (e) {
      match (K(Or,_(a),_(b))) {
        dexp first = plub( input, grammar, V(a), i, phase, memos );
        CASE (first) {
          match (K(Ok,_(pt),_(ni))) {
            answer = first;
          } else match (S(Bad)) {
            dexp second = plub( input, grammar, V(b), i, phase, memos );
            answer = second;
          }
        } ENDCASE;
      } else match (K(Seq,_(ctor),_(a),_(b))) {
        dexp first = plub( input, grammar, V(a), i, phase, memos );
        CASE (first) {
          match (K(Ok,_(pta),_(ni))) {
            dexp second = plub( input, grammar, V(b), gI(V(ni)), phase, memos );
            CASE (second) {
              match (K(Ok,_(ptb),_(ni))) {
                char *ctor = CONSCTORS(V(ctor));
                dexp tree = phase==1 ? mkcons( ctor, V(pta), V(ptb)) : Nil;
                answer = K(Ok,tree,V(ni));
              } otherwise(_) {
                answer = S(Bad);
              }
            } ENDCASE;
          } otherwise(_) {
            answer = S(Bad);
          }
        } ENDCASE;
      } else match (K(NT,_(nt))) {
        answer = plub( input, grammar, gM(grammar,V(nt)), i, phase, memos );
      } else match (K((..),_(lo),_(hi))) {
        if (i>=ARRAYSIZE(input)) {
          answer = S(Bad);
        } else {
          char c = gC(gA(input,i));
          if (c>=gC(V(lo)) && c<=gC(V(hi))) {
            dexp tree = phase==1 ? K(Char,mkchar(c)) : Nil;
            answer = K(Ok,tree,I(i+1));
          } else {
            answer = S(Bad);
          }
        }
      } else match (K(Nothing,_(what))) {
        dexp tree = phase==1 ? e : Nil;
        answer = K(Ok,tree,I(i));
      }
    } ENDCASE;

    pM(memos,key,answer);
  }

  A(answer);

  if (show) {
    spew(( "-> %5d ", s, i ));
    sldspew( e );
    sldspew( answer );
    spew(( "\n" ));
  }

  return answer;
}

dexp mouf( dexp input, dexp grammar, dexp e )
{
  dexp memos = EMAP();

  return iplub( input, grammar, e, 0, memos );

/*
  // Phase 0: fill out memos but don't build
  serial=0;
  plub( input, grammar, e, 0, 0, memos );

  // Phase 1: use memos and build
  serial=0;
  return plub( input, grammar, e, 0, 1, memos );
*/
}

dexp cleanup( dexp e );

dexp flatten_string( dexp l )
{
  char *s, *ss;
  dexp here;
  int length;

  // Find length.
  length = 0;
  here = l;
  while (1) {
    CASE (here) {
      match (K(string_node,K(Char,_(c)),_(rest))) {
        length++;
        here = V(rest);
      } else match (S(string_end)) {
        break;
      }
    } ENDCASE;
  }

  s = NCNEWC(char,length+1);

  // Copy chars out.
  here = l;
  ss = s;
  while (1) {
    CASE (here) {
      match (K(string_node,K(Char,_(c)),_(rest))) {
        *ss++ = gC(V(c));
        here = V(rest);
      } else match (S(string_end)) {
        break;
      }
    } ENDCASE;
  }
  A(ss-s==length);

  // Terminate.
  s[length] = 0;

  return mkstring( s );
}

dexp bsflatten( dexp e )
{
  //lspew( "bsf ", e );
  CASE (e) {
    match (K(Cons,_(a),K(Cons,S(list_end),Nil))) {
      return CONS(cleanup(V(a)),Nil);
    } else match (K(Cons,K(b_s,_(a),_(b)),_(d))) {
      return bsflatten(
        CONS( V(a), CONS( V(b), V(d) ) ) );
    } else match (K(Cons,K(Nothing,S(list_end)),Nil)) {
      return Nil;
    } else match (K(Cons,_(a),_(d))) {
      return CONS(cleanup(V(a)),bsflatten(V(d)));
    } else match (Nil) {
      return Nil;
    }
  } ENDCASE;
  return e;
}

dexp cleanup( dexp e )
{
  CASE (e) {
    match (K(string_node,_(c),_(rest))) {
      e = K(String,flatten_string( e ));
    } ornot;
  } ENDCASE;

  if (ISCONS(e)) {
    dexp ctor = CONSCTOR(e);
    dexp args = args2list( e );
    args = bsflatten( args );
    e = list2ctor( ctor, args );
  }

  return e;
}

dexp mrd_parse( dexp grammar, dexp top, dexp input )
{
  top = K(NT,top);

  grammar = binarize_seqs( grammar );
  grammar = charize_strings( grammar );

  dexp result = mouf( input, grammar, top );

A(result);

  CASE (result) {
    match (K(Ok,_(tree),_(nc))) {
      if (0 && gI(V(nc)) != ARRAYSIZE(input)) {
        err(( "Didn't consume input. %d %d", gI(V(nc)), ARRAYSIZE(input) ));
        result = S(Bad);
      }
    } ornot;
  } ENDCASE;

  CASE (result) {
    match (K(Ok,_(tree),_(nc))) {
      dexp tree = V(tree);
      tree = cleanup( tree );
      result = K(Ok,tree);
    } ornot;
  } ENDCASE;

  return result;
}
