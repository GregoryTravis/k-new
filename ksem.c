// $Id: ksem.c,v 1.12 2002/10/11 20:55:21 Administrator Exp $

#include "sexputil.h"

#include "ksem.h"
#include "ksym.h"

static sexp process_list( sexp lyst )
{
//SM(list,lyst);
  if (SEXP_IS_NIL( lyst )) {
    return lyst;
  } else if (SEXP_IS_CONS( lyst )) {
    return cons( ksem_process( car( lyst ) ), process_list( cdr( lyst ) ) );
  } else {
    SD( lyst );
    err(( "Bad lyst for process_list" ));
    return nil;
  }
}

static sexp process_class_body( sexp classname, sexp classbody )
{
  sexp s, ss, sss, ssss;
  sexp c;
  sexp declrec = nil;
  sexp exports = nil;
  sexp exporter = nil;
  sexp clasz = nil;
  sexp ctor = nil;
  sexp ctorparams = nil;

//SD(classbody);

  A(SEXP_IS_CONS(classbody));

  FORLIST( classline, classbody, {
    int public = 0;

    if (sexp_scan( classline, "(public %)", &s )) {
      public = 1;
    } else if (sexp_scan( classline, "(private %)", &s )) {
      public = 0;
    } else {
      SD( classline );
      err(( "Bad class decl\n" ));
    }

    if (sexp_scan( s, "(decl . %)", &ss )) {
      FORLIST( declitem, ss, {
        sexp name = car( declitem );
        declrec = snoc( declrec, declitem );

        if (public) {
          exports = cons( name, exports );
        }
      } );
    } else if (sexp_scan( s, "(function % % . %)", &ss, &sss, &ssss )) {
      sexp name = ss;
      sexp lambda = sexp_build( "(lambda % . %)", sss, ssss );
      sexp declitem = sexp_build( "(% %)", ss, lambda );
      declrec = snoc( declrec, declitem );

      if (EQ( name, classname )) {
        ctor = lambda;
      }

      if (public) {
        exports = cons( name, exports );
      }
    } else {
      SD( s );
      err(( "Bad class decl\n" ));
    }
  } );

  // Build exporter
  exporter = sexp_build( "(quote ())" );
  FORLIST( export, exports, {
    sexp getter = sexp_build( "(lambda () (return (var %)))", export );
    sexp setter = sexp_build( "(lambda (_val) (set! (var %) (var _val)))", export );
    sexp gpair = sexp_build( "(funcall (var cons) (quote get) %)", getter ); 
    sexp spair = sexp_build( "(funcall (var cons) (quote set) %)", setter );
    sexp gsassoc = sexp_build( "(funcall (var cons) % (funcall (var cons) % (quote ())))", gpair, spair );
    sexp gsentry = sexp_build( "(funcall (var cons) (quote %) %)", export, gsassoc );
    exporter = sexp_build( "(funcall (var cons) % %)", gsentry, exporter );
/*
    exporter =
      sexp_build(
        "(funcall (var cons) (funcall (var cons) (quote %) (funcall (var cons) (lambda () (var %)) (lambda (val) (set! (var %) (var val))))) %)",
        export, export, export, exporter );
*/
  } );

  exporter =
    sexp_build( "(lambda (name type) (return (funcall (var objectlookup) (var name) (var type) %)))",
      exporter );

  FORLIST( ctorparam, cadr( ctor ), {
    ctorparams = sexp_build( "((var %) . %)", ctorparam, ctorparams );
  } );

  clasz = sexp_build( "(lambda % (block (declrec . %) (funcall (var %) . %) (return %)))",
    cadr( ctor ), declrec, classname, ctorparams, exporter );

//SD(clasz);

  clasz = sexp_build( "(funcall (var cons) (quote class) %)", clasz );

  return clasz;
}

static sexp process_body( sexp lyst )
{
  sexp s, ss, sss;

//SM(body,lyst);
  if (SEXP_IS_NIL( lyst )) {
    return lyst;
  } else if (SEXP_IS_CONS( lyst )) {
    if (sexp_scan( car( lyst ), "(decl . %)", &s )) {
      return sexp_build( "((funcall (ilambda % . %) . %))",
        cars( s ), process_body( cdr( lyst ) ), process_list( cadrs( s ) ) );
    } else if (sexp_scan( car( lyst ), "(declrec . %)", &s )) {
      sexp decl = nil;
      sexp sets = nil;
      FORLIST( de, s, {
        decl = sexp_build( "((% (const 0)) . %)", car( de ), decl );
        sets = sexp_build( "((set! (var %) %) . %)", car( de ), cadr( de ), sets );
      } );
      return process_body(
        sexp_build( "((decl . %) (block . %) . %)",
          decl, sets, cdr( lyst ) ) );
    } else if (sexp_scan( car( lyst ), "(function % % . %)", &s, &ss, &sss )) {
      return process_body(
        sexp_build( "((decl (% (const 0)))(set! (var %) (lambda % . %)) . %)",
          s, s, ss, sss, cdr( lyst ) ) );
    } else if (sexp_scan( car( lyst ), "(gfunction % % . %)", &s, &ss, &sss )) {
      return process_body(
        sexp_build( "((gdecl (% (const 0)))(gset! (var %) (lambda % . %)) . %)",
          s, s, ss, process_body( sss ), cdr( lyst ) ) );
    } else if (sexp_scan( car( lyst ), "(class % %)", &s, &ss )) {
      sexp name = s;
      sexp statements = ss;

      return process_body(
        sexp_build( "((decl (% %)) . %)", s,
          process_class_body( s, ss ), cdr( lyst ) ) );
/*
    } else if (sexp_scan( car( lyst ), "(label %)", &s )) {
      return sexp_build(
        "((funcall (lambda (%) (set! (var %) (lambda () . %)) (funcall (var %))) (const 0)))",
        s, s, process_body( cdr( lyst ) ), s );
//        "((funcall (lambda (%) (fset! (lambda () (funcall (var %))) (var %) (lambda () . % ))) (const 0)))",
//        s, s, s, process_body( cdr( lyst ) ) );
*/
    } else {
      return cons( ksem_process( car( lyst ) ), process_body( cdr( lyst ) ) );
    }
  } else {
    err(( "Bad lyst for process_list" ));
    return nil;
  }
}

static sexp process_gdecl( sexp sem )
{
//SM(gdecl,sem);
  if (sem==nil) {
    return nil;
  } else if (SEXP_IS_CONS( sem )) {
    return sexp_build( "((gset! (var %) %) . %)",
      car( car( sem ) ),
      ksem_process( car( cdr( car( sem ) ) ) ),
      process_gdecl( cdr( sem ) ) );
  } else {
    SD(sem);
    err(( "Bad gdecls!" ));
    return nil;
  }
}

sexp ksem_process( sexp sem )
{
  sexp s, ss, sss, ssss;

//SM(process,sem);
  if (sexp_scan( sem, "(lambda % . %)", &s, &ss )) {
    return sexp_build( "(lambda % . %)", s, process_body( ss ) );
//  } else if (sexp_scan( sem, "((decl . %) . %)", &s, &ss )) {
//    return sexp_build( "((funcall (lambda % . %) . %))",
//      cars( s ), process_body( ss ), process_list( cadrs( s ) ) );
  } else if (sexp_scan( sem, "(gdecl . %)", &s )) {
    return sexp_build( "(block . %)", process_gdecl( s ) );
  } else if (sexp_scan( sem, "(const %)", &s )) {
    return sexp_build( "(const %)", s );
  } else if (sexp_scan( sem, "(var %)", &s )) {
    return sexp_build( "(var %)", s );
  } else if (sexp_scan( sem, "(show %)", &s )) {
    return sexp_build( "(show %)", ksem_process( s ) );
  } else if (sexp_scan( sem, "(return . %)", &s )) {
    return sexp_build( "(return . %)", process_list( s ) );
  } else if (sexp_scan( sem, "(goto %)", &s )) {
    return sexp_build( "(goto %)", s );
  } else if (sexp_scan( sem, "(label %)", &s )) {
    return sexp_build( "(label %)", s );
  } else if (sexp_scan( sem, "(gset! . %)", &s )) {
    return sexp_build( "(gset! . %)", s );
  } else if (sexp_scan( sem, "(funcall . %)", &s )) {
    return sexp_build( "(funcall . %)", process_list( s ) );
  } else if (sexp_scan( sem, "(if % % %)", &s, &ss, &sss )) {
    return sexp_build( "(if % % %)", s, ksem_process( ss ), ksem_process( sss ) );
  } else if (sexp_scan( sem, "(block . %)", &s )) {
    return sexp_build( "(block . %)", process_body( s ) );
  } else if (sexp_scan( sem, "(set! % %)", &s, &ss )) {
    if (sexp_scan( s, "(objectaccess % %)", &sss, &ssss )) {
      // Object field assignment
      return ksem_process(
        sexp_build( "(funcall (funcall (var %) (quote %) (quote set)) %)",
          sss, ssss, ss ) );
    } else {
      return sexp_build( "(set! % %)", s, ksem_process( ss ) );
    }
  } else if (sexp_scan( sem, "(callcc %)", &s )) {
    return sexp_build( "(callcc %)", ksem_process( s ) );
//  } else if (sexp_scan( sem, "(goto %)", &s )) {
//    return sexp_build( "(funcall (var %))", s );
  } else if (sexp_scan( sem, "(while % %)", &s, &ss )) {
    sexp label = ksym_new_sym();

    sexp exp = ksem_process( s );
    sexp body = ksem_process( ss );

    ksym_set_reason( label, "while label", cons( s, ss ) );

    return sexp_build(
      "(block (label %) (if % (block % (goto %)) (lambda () (const 0))))",
      label, exp, body, label );
  } else if (sexp_scan( sem, "(do % %)", &s, &ss )) {
    sexp label = ksym_new_sym();

    sexp body = ksem_process( s );
    sexp exp = ksem_process( ss );

    ksym_set_reason( label, "do label", cons( s, ss ) );

    return sexp_build(
      "(block (label %) % (if % (block (goto %)) (lambda () (const 0))))",
      label, body, exp, label );
  } else if (sexp_scan( sem, "(quote %)", &s )) {
    return sexp_build( "(const %)", s );
  } else if (sexp_scan( sem, "(include %)", &s )) {
    return sexp_build( "(include %)", s );
  } else if (sexp_scan( sem, "(objectaccess % %)", &s, &ss )) {
    return ksem_process( sexp_build( "(funcall (funcall (var %) (quote %) (quote get)))", s, ss ) );
  } else if (sexp_scan( sem, "(new %)", &s )) {
    return sexp_build( "(funcall (var cdr) (var %))", s );
  } else {
    SD( sem );
    err(( "ksem_process: unknown construct\n" ));
    return nil;
//    return sem;
  }
}
