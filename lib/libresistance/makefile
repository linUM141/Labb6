all: lib

program: lib
	gcc -L. -Wall -o test_main test_main.c -lresistance -Wl,-rpath=.

lib: libresistance.o
	gcc -shared -fPIC -o libresistance.so libresistance.o

libresistance.o: libresistance.c libresistance.h
	gcc -c -fPIC libresistance.c libresistance.h

clean:
	rm *.o
	rm *.so
	rm test_main

test: program
	./test_main

install: lib
	cp libresistance.so /usr/local/bin/libresistance.so

uninstall:
	rm /usr/local/bin/libresistance.so

docs: lib
	doxygen
	make -C docs/latex
	cp docs/latex/refman.pdf docs/documentation.pdf
