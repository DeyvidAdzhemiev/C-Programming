CC=gcc
AR=ar
INCLUDE=-I.
LIBDIR=-L.
DEBUG=
OPTIONS=$(DEBUG) $(INCLUDE)
COMPILE=$(CC) $(OPTIONS)
LINK=$(CC) $(DEBUG) $(LIBDIR)
SLINK=$(AR) -rv
RANLIB=ranlib

.c.o:
	echo target $@
	$(COMPILE) -c $< -o $@

liblist.a: list.o
	echo target $@
	$(SLINK) $@ $<
	$(RANLIB) $@

liblist.so: list.o
	echo target $@
	$(LINK) -shared -fPIC $< -lpthread -o $@

testlist_static: liblist.a testlist.o
	echo target $@
	$(LINK) testlist.o liblist.a -lpthread -o $@

testlist_dynamic: liblist.so testlist.o
	echo target $@
	$(LINK) testlist.o -llist -o $@

all: liblist.a liblist.so testlist_static testlist_dynamic
	echo target $@

clean:
	echo target $@
	rm -f *.o *.s *.a *.so testlist_static testlist_dynamic 

