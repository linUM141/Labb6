all: lib

program: lib
	gcc -L. -Wall -o test_main test_main.c -lpower -Wl,-rpath=.

lib: libpower.o
	gcc -shared -fPIC -o libpower.so libpower.o

libpower.o: libpower.c libpower.h
	gcc -c -fPIC libpower.c libpower.h

clean:
	rm *.o
	rm *.so
	rm test_main

test: program
	./test_main

install: lib
	cp libpower.so /usr/local/bin/libpower.so

uninstall:
	rm /usr/local/bin/libpower.so
