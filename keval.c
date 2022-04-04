// $Id: keval.c,v 1.17 2002/10/22 19:16:49 Administrator Exp $

#include <stdio.h>
#include <unistd.h>

#include "a.h"
#include "mem.h"
#include "sexp.h"

#include "kcps.h"
#include "kenv.h"
#include "kerr.h"
#include "kexec.h"
#include "kprim.h"
#include "kstruct.h"

static int dotrace = 0;

static sexp global_env = 0;

static int initted = 0;
void k_eval_init( void )
{
  sexp layer;

  if (initted)
    return;

  global_env = kenv_make_env();
  kprim_add_prims( global_env );

  initted = 1;
}

static sexp make_closure( sexp env, sexp lambda )
{
  return SEXP_MKCLOSURE( lambda, env, NULL );
}

static sexp feval_list( sexp env, sexp exps );

static sexp feval( sexp env, sexp exp )
{
  sexp s, ss, sss;

  A(SEXP_OK( env ));
  A(SEXP_OK( exp ));

  if (sexp_scan( exp, "(ffuncall . %)", &s )) {
    return sexp_build( "(tramp . %)", feval_list( env, s ) );
  } else if (sexp_scan( exp, "(lambda . %)", &s )) {
    return make_closure( env, exp );
//  } else if (SEXP_IS_SYMBOL( exp )) {
//    return kenv_get_env( env, exp );
  } else if (sexp_scan( exp, "(const %)", &s )) {
    return s;
  } else if (sexp_scan( exp, "(fset! % (var %) %)", &s, &ss, &sss )) {
    sexp kont = s;
    sexp var = ss;
    sexp val = sss;
    sexp funcall;

    kont = feval( env, kont );
    val = feval( env, val );
    KERRPUNTV(nil);

    kenv_put_env( env, var, val );
    KERRPUNTV(nil);

    funcall = sexp_build( "(tramp % %)", kont, val );
    KERRPUNTV(nil);

    return funcall;
  } else if (sexp_scan( exp, "(ftailcall %)", &s )) {
    sexp kont = s;

    kont = feval( env, kont );
    KERRPUNTV(nil);

    return sexp_build( "(tramp %)", kont );
  } else if (sexp_scan( exp, "(fgset! % (var %) %)", &s, &ss, &sss )) {
    sexp kont = s;
    sexp var = ss;
    sexp val = sss;
    sexp funcall;

    kont = feval( env, kont );
    val = feval( env, val );
    KERRPUNTV(nil);

    kenv_global_put_env( env, var, val );
    KERRPUNTV(nil);

    funcall = sexp_build( "(tramp % %)", kont, val );
    KERRPUNTV(nil);

    return funcall;
  } else if (sexp_scan( exp, "(var %)", &s )) {
    sexp val2 = kenv_get_env( env, s );
//SD(SEXP_PROPERTIES(s));
    KERRPUNTV(nil);
    return val2;
  } else if (sexp_scan( exp, "(fshow % %)", &s, &ss )) {
    sexp kont = s;
    sexp val = ss;
    sexp funcall;

    kont = feval( env, kont );
    val = feval( env, val );
    KERRPUNTV(nil);

    sexp_dump( val );
    fflush( stdout );

    funcall = sexp_build( "(tramp % ())", kont );
    KERRPUNTV(nil);

    return funcall;
  } else if (sexp_scan( exp, "(fif % % %)", &s, &ss, &sss )) {
    s = feval( env, s );
    if (s==true) {
      return feval( env, ss );
    } else if (s==false) {
      return feval( env, sss );
    } else {
      SD(s);
      kerr( "Bad value for conditional" );
      KERRPUNTV(nil);
      return nil;
    }
  } else if (sexp_scan( exp, "(finclude % %)", &s, &ss )) {
    sexp kont = s;
    sexp includee = ss;
    char *filename = SEXP_GET_STRING( ss );

    kont = feval( env, kont );

    k_exec_file( filename );
    KERRPUNTV(nil);

    return sexp_build( "(tramp %)", kont );
  } else {
    SD( env );
    SD( exp );
    err(( "Can't eval!" ));
    return nil;
  }
}

static sexp feval_list( sexp env, sexp exps )
{
  if (SEXP_IS_NIL( exps )) {
    return nil;
  } else if (SEXP_IS_CONS( exps )) {
    return cons( feval( env, car( exps ) ),
      feval_list( env, cdr( exps ) ) );
  } else {
    sexp_dump( exps );
    err(( "Bad feval list!" ));
    return nil;
  }
}

static sexp make_funcall_layer( sexp params, sexp args )
{
  if (SEXP_IS_CONS( params )) {
    if (!SEXP_IS_CONS( args )) {
      kerr( "Args do not match params" );
      KERRPUNTV(nil);
      return nil;
    } else {
      return cons( cons( car( params ), car( args ) ),
        make_funcall_layer( cdr( params ), cdr( args ) ) );
    }
  } else if (SEXP_IS_NIL( params )) {
    if (SEXP_IS_NIL( args )) {
      return nil;
    } else {
      kerr( "Args do not match params" );
      KERRPUNTV(nil);
      return nil;
    }
  } else {
    return cons( cons( params, args ), nil );
  }
}

static sexp eval_apply( sexp funcall )
{
  sexp s, ss, sss;

  if (sexp_scan( funcall, "(tramp % . %)", &s, &ss )) {
    sexp func = s;
    sexp args = ss;
    sexp lambda_params, lambda_body, lambda_env;

    if (SEXP_IS_NATIVE( func )) {
      sexp_native native = SEXP_GET_NATIVE( func );
      sexp kont = car( args );
      sexp real_args = cdr( args );
      sexp retval = (*native)( real_args );
      return sexp_build( "(tramp % %)", kont, retval );
    } else if (SEXP_IS_CLOSURE( func )) {
      sexp lambda = SEXP_GET_CLOSURE_CODE(func);
      sexp lambda_env = SEXP_GET_CLOSURE_ENV(func);
      sexp nuenv, nulayer;

      if (!sexp_scan( lambda, "(lambda % %)", &lambda_params, &lambda_body )) {
        SD( func );
        SD( lambda );
        err(( "Bad lambda in closure" ));
      }


      //nuenv = kenv_add_layer( lambda_env, lambda_params, args );
      nulayer = make_funcall_layer( lambda_params, args );

      if (KERR) {
        SD(lambda_params);
        SD(args);
      }
      KERRPUNTV(nil);
      nuenv = kenv_add_layer( lambda_env, nulayer );
      return feval( nuenv, lambda_body );
    } else {
      SD(func);
      err(( "Bad closure!" ));
    }
  } else {
    SD( funcall );
    err(( "Can't apply!" ));
    return nil;
  }
  return nil;
}

/*
static void eval_trampoline( sexp sem )
{
  sexp env = global_env;
  sexp topk = feval( env, sexp_parse( "(lambda () ())" ) );
  sexp topc = feval( env, sem );
  sexp tramp = sexp_build( "(tramp % %)", topc, topk );

  A(env);

  while (1) {
    tramp = eval_apply( tramp );

    KERRPUNT;

    if (cadr( tramp ) == topk)
      break;
  }
}
*/

static void eval_trampoline( sexp tramp, sexp topk )
{
  sexp closure, dummy;

  while (1) {
    if (sexp_scan( tramp, "(tramp % . %)", &closure, &dummy ) &&
        SEXP_IS_CLOSURE( closure ) &&
        SEXP_GET_CLOSURE_CODE( closure ) == topk) {
        break;
    }

    if (dotrace) {
      sexp trace = tramp;
      SD(trace);
    }

    tramp = eval_apply( tramp );

    KERRPUNT;
  }
}

void k_eval( char *filename, sexp sem )
{
  sexp env, topk;
  sexp fun, arg;
  sexp tramp;

  topk = sexp_build( "(lambda () ())" );

  A(SEXP_OK(env));
  A(sem);

  sem = kcps_convert( sem, topk );
  A(sem);

  sexp_dump_file( strkat( filename, ".cps.out" ), sem );

  KERRPUNT;

  fun = cadr( sem );
  arg = caddr( sem );

  fun = feval( global_env, fun );
  arg = feval( global_env, arg );

  tramp = sexp_build( "(tramp % %)", fun, arg );

  eval_trampoline( tramp, topk );
}
