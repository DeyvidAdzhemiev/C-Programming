CC=gcc
AR=ar
COMPILE=$(CC)
LINK=$(CC)
SLINK=$(AR) -rv

.c.o:
	$(COMPILE) -c $< -o $@

main: main.o
	$(LINK) main.o -o $@

static: static.o
	$(LINK) static.o -o $@

libours.a: our_lib.o
	$(SLINK) $@ our_lib.o
	ranlib libours.a

libours.so: our_lib.o
	$(LINK) -shared -fPIC $< -o $@

testlib_static: libours.a testlib.o
	$(LINK) testlib.o libours.a -o $@

testlib_dynamic: libours.a testlib.o
	$(LINK) -L. testlib.o -lours -o $@

all: main static libours.a libours.so testlib_static testlib_dynamic

clean:
	rm -f *.o *.s *.a *.so main static testlib_static testlib_dynamic 

