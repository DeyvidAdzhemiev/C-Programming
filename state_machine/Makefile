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

libstate.a: sm.o
	echo target $@
	$(SLINK) $@ $<
	$(RANLIB) $@

libstate.so: sm.o
	echo target $@
	$(LINK) -shared -fPIC $< -o $@

number_static: libstate.a number.o
	echo target $@
	$(LINK) number.o libstate.a -o $@

number_dynamic: libstate.so number.o
	echo target $@
	$(LINK) number.o -lstate -o $@

all: libstate.a libstate.so number_static number_dynamic
	echo target $@

clean:
	echo target $@
	rm -f *.o *.s *.a *.so teststate_* 

