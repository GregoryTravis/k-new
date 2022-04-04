{
  top_statement = top_statement( ws, statement, ws );

  operator = ai( opchar, operator )
           | ain( opchar );
  opchar = '!' | ('#'..'&') | ('*'..'+') | ('-'..'/') | ':' | ('<'..'@')
         | '\\' | ('^'..'`') | '|' | '~';

  ws = ai( wschar, ws )
     | Nothing( ainn );
  wschar = ' ' | '\t' | '\n';

  ident = regular_ident | opname;
  regular_ident = ai( idchar, regular_ident )
         | ain( idchar );
  idchar = 'a'..'z' | 'A'..'Z' | '0'..'9' | '_';
  opname = opname( '(', operator, ')' );

  exp = opexp( baseexp, ws, operator, ws, exp ) | baseexp;
  pexp = pexp( '(', ws, exp, ws, ')' );
  baseexp = construction | array | pexp | tuple | list | float
          | integer | ident | literal;

  construction = construction( ident, ws, '(', ws, explist, ws, ')' );
  list = list( '[', ws, explist, ws, ']' );
  array = array( '{', ws, explist, ws, '}' );
  tuple = tuple( '(', ws, explist, ws, ')' );

  explist = el( exp, ws, ',', ws, explist )
          | ellast( exp )
          | Nothing( eln );

  integer = hex_integer | octal_integer | decimal_integer;

  octal_integer = octal_integer( '0', 'o', oclist );
  decimal_integer = decimal_integer_explicit( '0', 'd', dclist )
                  | decimal_integer( dclist );
  hex_integer = hex_integer( '0', 'x', hclist );

  octalchar = '0' .. '7';
  decimalchar = '0' .. '9';
  hexchar = '0' .. '9' | 'a' .. 'f' | 'A' .. 'F';

  dclist = ai( decimalchar, dclist ) | ain( decimalchar );
  hclist = ai( hexchar, hclist ) | ain( hexchar );
  oclist = ai( octalchar, oclist ) | ain( octalchar );

  float = floatparts( dclist, '.', dclist );

  exp_statement = exp_statement( exp, ws, ';' );
  block_statement = block_statement( '{', ws, statement_list, ws, '}' );
  statement_list = sl( statement, ws, statement_list ) | Nothing( sln );
  statement = exp_statement | block_statement;

  escaped_char = EChar( "\\t" ) | EChar( "\\\\" )
               | EChar( "\\\"" ) | EChar( "\\\'" ) | EChar( "\\n" );

  numeric_char = octal_numeric_char | decimal_numeric_char | hex_numeric_char;

  octal_numeric_char = octal_numeric_char( '\\', 'o', oclist );
  decimal_numeric_char = decimal_numeric_char( '\\', 'd', dclist );
  hex_numeric_char = hex_numeric_char( '\\', 'x', hclist );

  other_than_double_quote = '\x00'..'!' | '#'..'\x7f';
  other_than_single_quote = '\x00'..'&' | '('..'\x7f';
  double_quote_char = escaped_char | numeric_char | other_than_double_quote;
  single_quote_char = escaped_char | numeric_char | other_than_single_quote;

  literal = char_literal | string_literal;
  char_literal = char_literal( '\'', single_quote_char, '\'' );
  string_literal = string_literal( '\"', stringchars, '\"' );
  stringchars = ai( double_quote_char, stringchars )
              | ain( double_quote_char );
}
