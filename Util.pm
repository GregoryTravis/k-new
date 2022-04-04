#!/usr/bin/perl -w

use strict;

package Util;

sub load_bindings( $ )
{
  my ($makefile) = @_;
  my $bindings = {};
  open( MAKEFILE, $makefile ) || die $!;
  while (<MAKEFILE>) {
    if (/^(\S+)\s*=\s(.*)$/) {
      my $name = $1;
      my $value = $2;
      $bindings->{$name} = $value;
    }
  }
  close( MAKEFILE );
  return $bindings;
}

1;
