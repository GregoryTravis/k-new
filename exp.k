{
  exp = lo( id, sufs );
  sufs = more( suf, sufs ) | suf;
  suf = suf( '+', id );

  id = '0' .. '9';
  top = exp;
}
