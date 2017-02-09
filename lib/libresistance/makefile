all: lib

program: lib
	gcc -L. -Wall -o test_main test_main.c -lresistance -Wl,-rpath=.

lib: libresistance.o
	gcc -shared -fPIC -o libresistance.so libresistance.o

#test_main.o: test_main.c
#	gcc -c test_main.c

libresistance.o: libresistance.c libresistance.h
	gcc -c -fPIC libresistance.c libresistance.h

#c_functions.o: c_functions.c c.h
#	gcc -c c_functions.c c.h

#b_functions.o: b_functions.c b.h
#	gcc -c b_functions.c b.h

#a_functions.o: a_functions.c a.h
#	gcc -c a_functions.c a.h

clean:
	rm *.o
#	rm bin/program1

test: program
	./test_main

install: program
	cp bin/program1 /usr/local/bin/program1

uninstall:
	rm /usr/local/bin/program1
