{
  lambda = lambda( "lambda", ws, '(', ws,
    formal_paramlist, ws, ')', ws, statement );

  formal_paramlist = el( formal_param, ws, ',', ws, formal_paramlist )
                   | ellast( formal_param )
                   | Nothing( eln );

  formal_param = formal_param( ident );

  exp = lambda;
}
