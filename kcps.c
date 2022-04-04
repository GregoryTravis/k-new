// $Id: kcps.c,v 1.14 2002/09/16 17:08:47 Administrator Exp $

#include "sexp.h"

#include "kcps.h"
#include "ksym.h"

static sexp convert_block( sexp stmts, sexp kont );

static sexp convert_funcall( sexp sem, sexp kont, sexp accum )
{
  A(SEXP_OK(sem));
  A(SEXP_OK(kont));
  A(SEXP_OK(accum));

  if (SEXP_IS_NIL( sem )) {
    sexp func = car( accum );
    sexp args = cdr( accum );
    return sexp_build( "(ffuncall % % . %)", func, kont, args );
  } else if (SEXP_IS_CONS( sem )) {
    sexp arg = ksym_new_sym();

    ksym_set_reason( arg, "cps funcall arg", L2( sem, kont ) );

    return kcps_convert( car( sem ),
      sexp_build( "(lambda (%) %)", arg,
        convert_funcall( cdr( sem ), kont, snoc( accum, sexp_build( "(var %)", arg ) ) ) ) );

  } else {
    err(( "Bad funcall" ));
    return nil;
  }
}

static sexp convert_statement( sexp stmt, sexp kont )
{
  sexp s, ss, sss;
  sexp arg;

  A(SEXP_OK(stmt));
  A(SEXP_OK(kont));

  // These two return cases should be combined with flatten
  if (sexp_scan( stmt, "(return %)", &s )) {
    return kcps_convert( s, sexp_build( "(var Kreturn)" ) );
  } else if (sexp_scan( stmt, "(block . %)", &s )) {
    return convert_block( s, kont );
  } else if (sexp_scan( stmt, "(return)" )) {
    return sexp_build( "(ffuncall (var Kreturn))" );
  } else if (sexp_scan( stmt, "(include %)", &s )) {
    return sexp_build( "(finclude % %)", kont, s );
  } else {
    arg = ksym_new_sym();

    ksym_set_reason( arg, "cps exp->stmt kont wrapper", stmt );

    // assume it's an expression-statement
    return kcps_convert( stmt, kont );
//      sexp_build( "(lambda (%) (ffuncall %))", arg, kont ) );
  }
}

static sexp convert_block( sexp stmts, sexp kont )
{
  sexp s, ss, sss;

  A(SEXP_OK(stmts));
  A(SEXP_OK(kont));

  if (SEXP_IS_NIL( stmts )) {
    return sexp_build( "(ffuncall %)", kont );
  } else if (SEXP_IS_CONS( stmts )) {
    sexp carr = car( stmts );
    sexp cdrr = cdr( stmts );

    if (sexp_scan( carr, "(label %)", &s )) {
      sexp dummy = ksym_new_sym();

      ksym_set_reason( dummy, "label recursive param", stmts );

      return sexp_build(
        "(ffuncall (lambda (%) (fset! (lambda (%) (ffuncall (var %))) (var %) (lambda () %))) (const 0))",
        s, dummy, dummy, s, convert_block( cdrr, kont ), s );
    } else if (sexp_scan( carr, "(goto %)", &s )) {
      return sexp_build( "(ftailcall (var %))", s );
    } else {
      sexp dummy = ksym_new_sym();

      ksym_set_reason( dummy, "cps inner block", stmts );

      return convert_statement( car( stmts ),
        sexp_build( "(lambda % %)", dummy,
          convert_block( cdr( stmts ), kont ) ) );
    }
  } else {
    err(( "Bad blambda" ));
    return nil;
  }
  return nil;
}

sexp kcps_convert( sexp sem, sexp kont )
{
  sexp s, ss, sss;
  int internalp=0;

  A(SEXP_OK(sem));
  A(SEXP_OK(kont));

  if (sexp_scan( sem, "(funcall . %)", &s )) {
    return convert_funcall( s, kont, nil );
  } else if (sexp_scan( sem, "(lambda % . %)", &s, &ss ) ||
             sexp_scan( sem, "(ilambda % . %)", &s, &ss )) {
    int internal;
    sexp lambda, dummy;
    sexp kontname = nil;

    sexp body = ss;

    // Is it internal
    internal = sexp_scan( sem, "(ilambda . %)", &dummy );

    if (internal) {
      kontname = ksym_new_sym();
      ksym_set_reason( kontname, "ilambda kont", sem );
    } else {
      kontname = S(Kreturn);
    }

    //body = convert_lambda_body( body );
    body = convert_block( body, sexp_build( "(var %)", kontname ) );

    lambda = sexp_build( "(lambda (% . %) %)", kontname, s, body );
    return sexp_build( "(ffuncall % %)", kont, lambda );
  } else if (sexp_scan( sem, "(set! % %)", &s, &ss )) {
    sexp arg;

    arg = ksym_new_sym();

    ksym_set_reason( arg, "cps set! arg", sem );

    return kcps_convert( ss,
      sexp_build( "(lambda (%) (fset! % % (var %)))", arg, kont, s, arg ) );
  } else if (sexp_scan( sem, "(gset! % %)", &s, &ss )) {
    sexp arg;

    arg = ksym_new_sym();

    ksym_set_reason( arg, "cps gset! arg", sem );

    return kcps_convert( ss,
      sexp_build( "(lambda (%) (fgset! % % (var %)))", arg, kont, s, arg ) );
  } else if (sexp_scan( sem, "(show %)", &s ) ) {
    sexp arg;

    arg = ksym_new_sym();

    ksym_set_reason( arg, "cps fshow arg", sem );

    return kcps_convert( s,
      sexp_build( "(lambda (%) (fshow % (var %)))", arg, kont, arg ) );
  } else if (sexp_scan( sem, "(if % % %)", &s, &ss, &sss )) {
    sexp arg = ksym_new_sym();

    ksym_set_reason( arg, "cps if arg", sem );

    return kcps_convert( s,
      sexp_build( "(lambda (%) (fif (var %) % %))", arg, arg,
        convert_statement( ss, kont ),
        convert_statement( sss, kont ) ) );
  } else if (sexp_scan( sem, "(callcc %)", &s )) {
    sexp proc = ksym_new_sym();
    sexp dummykont = ksym_new_sym();
    sexp val = ksym_new_sym();

    ksym_set_reason( proc, "callcc proc cps", sem );
    ksym_set_reason( dummykont, "callcc dummy kont", sem );
    ksym_set_reason( val, "callcc dummy kont val", sem );

    return kcps_convert( s,
      sexp_build(
        "(lambda (%) (ffuncall (var %) % %))",
        proc, proc, kont,
        sexp_build(
          "(lambda (% %) (ffuncall % (var %)))",
          dummykont, val, kont, val ) ) );

  } else {
    return sexp_build( "(ffuncall % %)", kont, sem );
  }
}
