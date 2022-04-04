#!/usr/bin/perl

$default_grammar = "kp";

if (@ARGV > 0) {
  $grammar = $ARGV[0];
} else {
  $grammar = $default_grammar;
}

&cmd( "ccc -vb -b -u ${grammar}.ccc" );
&cmd( "${grammar} ${grammar}.input.txt" );

sub cmd {
  my ($cmd) = @_;
  print "$cmd\n";
  my $ret = system( $cmd );
  #print "RET $ret\n";
  return $ret==0;
}
