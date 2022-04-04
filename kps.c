// $Id: kps.c,v 1.29 2002/10/22 19:16:49 Administrator Exp $

#include "kerr.h"
#include "kmisc.h"
#include "kps.h"
#include "sexp.h"

static sexp pts( sexp p );

static sexp pts_list( sexp p )
{
  if (SEXP_IS_NIL( p )) {
    return p;
  } else if (SEXP_IS_CONS( p )) {
    return cons( pts( car( p ) ), pts_list( cdr( p ) ) );
  } else {
    SD( p );
    err(( "kps_convert: unknown construct" ));
    return nil;
    //return pts( p );
  }
}

static sexp pts_decls( sexp decls )
{
  sexp s, ss, sss;

  if (SEXP_IS_NIL( decls )) {
    return decls;
  } else if (SEXP_IS_CONS( decls ) && sexp_scan( car( decls ), "(adecl default % %)", &s, &ss )) {
    return cons( sexp_build( "(% %)", s, pts( ss ) ), pts_decls( cdr( decls ) ) );
  } else {
    SD( decls );
    err(( "Bad decls list for pts_decls" ));
    return nil;
  }
}

static sexp pts( sexp p )
{
  sexp dummy;
  sexp s, ss, sss, ssss;

  if (sexp_scan( p, "(top default (program default (statement_list default %)))", &s )) {
    return sexp_build( "(funcall (lambda () . %))", pts_list( s ) );
  } else if (sexp_scan( p, "(statement expressionstatement %)", &s )) {
    return pts( s );
  } else if (sexp_scan( p, "(expression assignment % %)", &s, &ss )) {
    return sexp_build( "(set! % %)", pts( s ), pts( ss ) );
  } else if (sexp_scan( p, "(expression variable (variable default true))" )) {
    return sexp_build( "(const #t)" );
  } else if (sexp_scan( p, "(expression variable (variable default false))" )) {
    return sexp_build( "(const #f)" );
  } else if (sexp_scan( p, "(expression variable (variable default %))", &s )) {
//SD(SEXP_PROPERTIES(s));
    return sexp_build( "(var %)", s );
  } else if (sexp_scan( p, "(statement block (block default %))", &s )) {
    return sexp_build( "(block . %)", pts_list( s ) );
  } else if (sexp_scan( p, "(expression lambda (lambda default lambda (arglist default %) \
    (block default %)))", &s, &ss )) {
    return sexp_build( "(lambda % . %)", s, pts_list( ss ) );
  } else if (sexp_scan( p, "(expression string %)", &s )) {
    return sexp_build( "(const %)", s );
  } else if (sexp_scan( p, "(expression integer %)", &s )) {
    int i;
    if (!sscanf( STR(s), "%d", &i )) {
      err(( "Can't parse integer %s\n", STR( s ) ));
    }
    s = SEXP_MKINT( i );
    return sexp_build( "(const %)", s );
  } else if (sexp_scan( p, "(expression boolconst %)", &s )) {
    int b = !strcmp( STR(s), "true" );
    return sexp_build( "(const %)", SEXP_MKBOOLEAN( b ) );
  } else if (sexp_scan( p, "(expression nil %)", &s )) {
    return sexp_build( "(const ())" );
  } else if (sexp_scan( p, "(statement returnargs return %)", &s )) {
    return sexp_build( "(return %)", pts( s ) );
  } else if (sexp_scan( p, "(statement returnnoargs return)" )) {
    return sexp_build( "(return)" );
  } else if (sexp_scan( p, "(expression show show %)", &s )) {
    return sexp_build( "(show %)", pts( s ) );
  } else if (sexp_scan( p, "(expression funcall % (paramlist default %))", &s, &ss )) {
    return sexp_build( "(funcall % . %)", pts( s ), pts_list( ss ) );
  } else if (sexp_scan( p, "(statement if (if ifelse if % % else %))", &s, &ss, &sss )) {
    return sexp_build( "(if % % %)", pts( s ), pts( ss ), pts( sss ) );
  } else if (sexp_scan( p, "(statement if (if if if % %))", &s, &ss )) {
    return sexp_build( "(if % % (lambda () (const 0)))", pts( s ), pts( ss ) );
  } else if (sexp_scan( p, "(expression opexpr (opexpr % % % %))", &dummy, &s, &ss, &sss )) {
    return sexp_build( "(funcall (var %) % %)", ss, pts( s ), pts( sss ) );
  } else if (sexp_scan( p, "(block default %)", &s )) {
    return sexp_build( "(block . %)", pts_list( s ) );
  } else if (sexp_scan( p, "(elsepart block %)", &s )) {
    return pts( s );
  } else if (sexp_scan( p, "(elsepart if %)", &s )) {
    return pts( s );
  } else if (sexp_scan( p, "(statement decls var (decllist default %))", &s )) {
    return sexp_build( "(decl . %)", pts_decls( s ) );
  } else if (sexp_scan( p, "(statement export (export decls (decllist default %)))", &s )) {
    return sexp_build( "(gdecl . %)", pts_decls( s ) );
  } else if (sexp_scan( p, "(statement function (function default fun % (arglist default %) (block default %)))", &s, &ss, &sss )) {
    return sexp_build( "(function % % . %)", s, ss, pts_list( sss ) );
  } else if (sexp_scan( p, "(statement export (export fun (function default fun % (arglist default %) (block default %))))", &s, &ss, &sss )) {
    return sexp_build( "(gfunction % % . %)", s, ss, pts_list( sss ) );
  } else if (sexp_scan( p, "(statement import (importspec default %))", &s )) {
    return sexp_build( "(funcall (var import) (const %))", SEXP_MKSTRING( STR(s) ) );
  } else if (sexp_scan( p, "(statement include %)", &s )) {
    return sexp_build( "(include %)", s );
  } else if (sexp_scan( p, "(statement label %)", &s )) {
    return sexp_build( "(label %)", s );
  } else if (sexp_scan( p, "(statement goto %)", &s )) {
    return sexp_build( "(goto %)", s );
  } else if (sexp_scan( p, "(statement while (while while % %))", &s, &ss )) {
    return sexp_build( "(while % %)", pts( s ), pts( ss ) );
  } else if (sexp_scan( p, "(statement for (for for % % % %))", &s, &ss, &sss, &ssss )) {
    return sexp_build( "(block % (while % (block % %)))", pts( s ), pts( ss ), pts( ssss ), pts( sss ) );
  } else if (sexp_scan( p, "(statement for (for forwithdecl (fordecls default (decllist default %)) % % %))", &s, &ss, &sss, &ssss )) {
    sexp decls = s;
    sexp test = ss;
    sexp update = sss;
    sexp block = ssss;

    return sexp_build( "(block (decl . %) (while % (block % %)))",
      pts_decls( decls ), pts( test ), pts( block ), pts( update ) );
  } else if (sexp_scan( p, "(statement do (do do % %))", &s, &ss )) {
    return sexp_build( "(do % %)", pts( s ), pts( ss ) );
  } else if (sexp_scan( p, "(expression callcc (callcc default %))", &s )) {
    return sexp_build( "(callcc %)", pts( s ) );
  } else if (sexp_scan( p, "(expression paren %)", &s )) {
    return pts( s );
  } else if (sexp_scan( p, "(expression quoteatom %)", &s )) {
    return sexp_build( "(quote %)", s );
  } else if (sexp_scan( p, "(statement class (class default % (class_statement_list default %)))", &s, &ss )) {
    return sexp_build( "(class % %)", s, pts_list( ss ) );
  } else if (sexp_scan( p, "(class_statement modified (class_access_modifier public public) %)", &s )) {
    return sexp_build( "(public %)", pts( s ) );
  } else if (sexp_scan( p, "(class_statement unmodified %)", &s )) {
    return sexp_build( "(private %)", pts( s ) );
  } else if (sexp_scan( p, "(expression objectaccess (objectaccess default % %))", &s, &ss )) {
    return sexp_build( "(objectaccess % %)", s, ss );
  } else if (sexp_scan( p, "(expression new %)", &s )) {
    return sexp_build( "(new %)", s );
  } else {
    SD( p );
    err(( "kps_convert: unknown construct" ));
    return nil;
  }
}

sexp k_parse_to_semantic( sexp parse )
{
  sexp sem;

  A(parse);

  sem = pts( parse );

  return sem;
}
