// $Id: kprim.c,v 1.13 2002/10/08 18:43:00 Administrator Exp $

#include "sexp.h"

#include "kenv.h"
#include "kprim.h"
#include "kprim_import.h"
#include "kprim_list.h"
#include "kprim_numop.h"
#include "kprim_boolean.h"
#include "kprim_reflect.h"

void kprim_add_prims( sexp env )
{
  kenv_global_put_env( env, mksym( "+" ), SEXP_MKNATIVE(numop_plus) );
  kenv_global_put_env( env, mksym( "-" ), SEXP_MKNATIVE(numop_minus) );
  kenv_global_put_env( env, mksym( "*" ), SEXP_MKNATIVE(numop_times) );
  kenv_global_put_env( env, mksym( "/" ), SEXP_MKNATIVE(numop_divided) );

  kenv_global_put_env( env, mksym( "==" ), SEXP_MKNATIVE(condop_dequals) );
  kenv_global_put_env( env, mksym( "!=" ), SEXP_MKNATIVE(condop_dnequals) );
  kenv_global_put_env( env, mksym( "<" ), SEXP_MKNATIVE(condop_lt) );
  kenv_global_put_env( env, mksym( ">" ), SEXP_MKNATIVE(condop_gt) );
  kenv_global_put_env( env, mksym( "<=" ), SEXP_MKNATIVE(condop_lte) );
  kenv_global_put_env( env, mksym( ">=" ), SEXP_MKNATIVE(condop_gte) );

  kenv_global_put_env( env, mksym( "&&" ), SEXP_MKNATIVE(boolop_andand) );
  kenv_global_put_env( env, mksym( "||" ), SEXP_MKNATIVE(boolop_oror) );

  ADDPRIM( env, cons );
  ADDPRIM( env, car );
  ADDPRIM( env, cdr );
  ADDPRIM( env, import );

  ADDPRIM( env, closure_get_code );

  kenv_global_put_env( env, mksym( "nil" ), nil );
}
