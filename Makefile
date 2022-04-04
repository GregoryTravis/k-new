# $Id: Makefile,v 1.17 2002/10/08 18:42:59 Administrator Exp $

CFLAGS = -g -Wreturn-type -Werror-implicit-function-declaration
LDFLAGS = -g

SEXP_OBJS = sexp.o sbuild.o sparse.o
LIB_OBJS = $(SEXP_OBJS) mem.o spew.o
PARSER_OBJS = kp.yy.o kp.tab.o

K_OBJS = $(LIB_OBJS) $(PARSER_OBJS) k.o kexec.o kfile.o kerr.o kps.o \
  kunparse.o keval.o kcps.o ksym.o kinit.o kprim.o kenv.o growbuf.o \
  strm.o sstrm.o fstrm.o kprim_numop.o kprim_list.o ksem.o sexputil.o \
  kprim_import.o kprim_boolean.o kprim_reflect.o

UMM_K_OBJS = kfile.o keval.o kp.yy.o kp.tab.o kps.o kmisc.o kerr.o \
  klayer.o kvalue.o kinit.o kunparse.o kexec.o katom.o kcps.o ktree.o ksym.o

PARSER_GENERATED = kp.c kp.output kp.tab.c kp.tab.o kp.tab.h kp.exe kp.grammar \
  kp.y kp.l kp.yy.c kp.h kp.yy.c kp.yy.o
GENERATED = k.exe shavtest.exe *.o $(PARSER_GENERATED)
COMMON_DEPS = kstruct.h

k: $(K_OBJS)
	gcc -Lgc6.0/.libs $(LDFLAGS) -o k $(K_OBJS) -lgc

shavtest: shavtest.o shav.o mem.o spew.o
	gcc -Lgc6.0/.libs $(LDFLAGS) -o shavtest shavtest.o shav.o mem.o spew.o -lgc

clean:
	rm -f $(GENERATED)

test: k
	@utest

shavtest.o: shavtest.c shav.h
	gcc $(CFLAGS) -c shavtest.c

shav.o: shav.c shav.h
	gcc $(CFLAGS) -c shav.c

spew.o: spew.c
	gcc $(CFLAGS) -c spew.c

mem.o: mem.c
	gcc $(CFLAGS) -c -Igc6.0/include mem.c

k.o: k.c $(COMMON_DEPS)
	gcc $(CFLAGS) -c k.c

kp.yy.o: kp.ccc
	ccc -vb -u kp.ccc

kp.tab.o: kp.ccc
	ccc -vb -u kp.ccc

kp.h: kp.ccc
	ccc -vb -u kp.ccc

keval.o: keval.c keval.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c keval.c

kfile.o: kfile.c kfile.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c kfile.c

kps.o: kps.c kps.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c kps.c

kmisc.o: kmisc.c kmisc.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c kmisc.c

kerr.o: kerr.c kerr.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c kerr.c

klayer.o: klayer.c klayer.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c klayer.c

kvalue.o: kvalue.c kvalue.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c kvalue.c

kinit.o: kinit.c kinit.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c kinit.c

kunparse.o: kunparse.c kunparse.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c kunparse.c

kexec.o: kexec.c kexec.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c kexec.c

katom.o: katom.c katom.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c katom.c

kcps.o: kcps.c kcps.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c kcps.c

ktree.o: ktree.c ktree.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c ktree.c

ksym.o: ksym.c ksym.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c ksym.c

sexp.o: sexp.c sexp.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c sexp.c

sbuild.o: sbuild.c sbuild.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c sbuild.c

sparse.o: sparse.c sparse.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c sparse.c

kprim.o: kprim.c kprim.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c kprim.c

kenv.o: kenv.c kenv.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c kenv.c

growbuf.o: growbuf.c growbuf.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c growbuf.c

strm.o: strm.c strm.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c strm.c

sstrm.o: sstrm.c sstrm.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c sstrm.c

fstrm.o: fstrm.c fstrm.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c fstrm.c

kprim_numop.o: kprim_numop.c kprim_numop.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c kprim_numop.c

kprim_list.o: kprim_list.c kprim_list.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c kprim_list.c

ksem.o: ksem.c ksem.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c ksem.c

sexputil.o: sexputil.c sexputil.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c sexputil.c

kprim_import.o: kprim_import.c kprim_import.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c kprim_import.c

kprim_boolean.o: kprim_boolean.c kprim_boolean.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c kprim_boolean.c

kprim_reflect.o: kprim_reflect.c kprim_reflect.h $(COMMON_DEPS)
	gcc $(CFLAGS) -c kprim_reflect.c
