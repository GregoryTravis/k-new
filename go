#!/usr/bin/perl

sub cmd {
  my ($cmd) = @_;
  print "$cmd\n";
  my $ret = system( $cmd );
  #$ret /= 256;
  die "error: $cmd: $ret" if ($ret != 0);
  #print "RET $ret\n";
  return $ret==0;
}

&cmd( "make" );
&cmd( "k k.k" );
#&cmd( "k primes.k" );
#&cmd( "cat k.postsem.out" );
