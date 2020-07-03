CC=gcc
AR=ar
COMPILE=$(CC)
LINK=$(CC)
SLINK=$(AR) -rv

.c.o:
	$(COMPILE) -c -I. $< -o $@

libqueue.a: queue_stat.o
	$(SLINK) $@ queue_stat.o
	ranlib $@

libqueue.so: queue_stat.o
	$(LINK) -shared -fPIC $< -o $@

testqueue_static: libqueue.a test_queue.o
	$(LINK) test_queue.o libqueue.a -o $@

testqueue_dynamic: libqueue.so test_queue.o
	$(LINK) -L. test_queue.o -lqueue -o $@

all: libqueue.a libqueue.so testqueue_static testqueue_dynamic

clean:
	rm -f *.o *.s *.a *.so testqueue_static testqueue_dynamic

