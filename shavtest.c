// $Id: shavtest.c,v 1.1 2002/08/05 16:00:11 Administrator Exp $

#include "shav.h"

int main( void )
{
  shav *s0, *s1s, *s1, *s2s, *s2s2, *s2, *si, *si2, *si3;

  s0 = make_shav_string( "sss" );
  printf( "%s\n", get_string( s0 ) );

  s1s = make_shav_string( "eee" );
  s1 = make_shav_hash();
  put_hash( s1, "ya", s1s );
  printf( "%s\n", get_string( get_hash( s1, "ya" ) ) );

  s2s = make_shav_string( "ooo" );
  s2s2 = make_shav_string( "iii" );
  s2 = make_shav_vec();
  put_vec( s2, 0, s2s );
  printf( "%s\n", get_string( get_vec( s2, 0 ) ) );
  put_vec( s2, 3, s2s2 );
  printf( "%s\n", get_string( get_vec( s2, 3 ) ) );

  si = make_shav_hash();
  put_hash( si, "a", make_shav_string( "10" ) );
  put_hash( si, "b", make_shav_string( "20" ) );
  put_hash( si, "c", make_shav_string( "30" ) );

  si2 = make_shav_vec();
  put_vec( si2, 3, si );
  put_vec( si2, 5, make_shav_string( "vvv" ) );

  si3 = make_shav_hash();
  put_hash( si3, "hh", si );
  put_hash( si3, "vv", si2 );

  shav_dump( si3 );

  return 0;
}
