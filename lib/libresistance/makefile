all: lib

program: lib
	gcc -L. -Wall -o test_main test_main.c -lresistance -Wl,-rpath=.

lib: libresistance.o
	gcc -shared -fPIC -o libresistance.so libresistance.o

libresistance.o: libresistance.c libresistance.h
	gcc -c -fPIC libresistance.c libresistance.h

clean:
	rm *.o

test: program
	./test_main

install: program
	cp bin/program1 /usr/local/bin/program1

uninstall:
	rm /usr/local/bin/program1
