// $Id: kenv.h,v 1.2 2002/09/12 16:29:33 Administrator Exp $

#ifndef _kenv_h_
#define _kenv_h_

#include "sexp.h"

sexp kenv_make_env( void );
sexp kenv_get_env( sexp env, sexp name );
void kenv_put_env( sexp env, sexp name, sexp value );
void kenv_global_put_env( sexp env, sexp name, sexp value );
sexp kenv_add_layer( sexp env, sexp layer );

#if 0
sexp kenv_make_env( void );
void kenv_put_env( sexp env, sexp name, sexp value );
sexp kenv_get_env( sexp env, sexp name );
sexp kenv_add_layer( sexp env, sexp params, sexp args );
sexp kenv_add_to_layer( sexp layer, sexp name, sexp value );
sexp kenv_get_layer( sexp env, int which );
void kenv_set_layer( sexp env, int which, sexp layer );
sexp kenv_add_whole_layer( sexp env, sexp layer );
sexp kenv_make_layer( void );
#endif

#endif /* _kenv_h_ */
