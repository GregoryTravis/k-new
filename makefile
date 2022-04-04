# $Id: makefile,v 1.3 2004/08/09 19:14:32 greg Exp $

generated = grammar.c grammar.h

#prof_flags = -pg
prof_flags =
opt_flags = -O6

cflags = -g -Wall -Wno-unused-variable $(opt_flags) $(prof_flags)
ldflags =

exes = smrdgen k

all: exes

exes:
	depbuild $(exes)

clean:
	rm -f $(exes) *.o $(generated) t/*/*.o t/*/*.out

test: exes
	runtests
