all: program

program: lib
	gcc -L./lib -Wall -o electrotest main.c -lresistance -lcomponent -Wl,-rpath=./lib

libInstall: lib
	cp lib/libresistance.so /usr/local/bin/libresistance.so
	cp lib/libcomponent.so /usr/local/bin/libcomponent.so

lib: libresistance.o libcomponent.o
	gcc -shared -fPIC -o lib/libresistance.so libresistance.o
	gcc -shared -fPIC -o lib/libcomponent.so libcomponent.o

libresistance.o: lib/libresistance/libresistance.c lib/libresistance/libresistance.h
	gcc -c -fPIC lib/libresistance/libresistance.c lib/libresistance/libresistance.h

libcomponent.o: lib/libcomponent/libcomponent.c lib/libcomponent/libcomponent.h
	gcc -c -fPIC lib/libcomponent/libcomponent.c lib/libcomponent/libcomponent.h

clean:
	rm *.o
	rm lib/*.so
	rm electrotest

test: program
	./test_main

install: libInstall
	gcc -L/usr/local/bin -Wall -o electrotest main.c -lresistance -Wl,-rpath=/usr/local/bin
	cp electrotest /usr/local/bin/electrotest

uninstall:
	rm /usr/local/bin/libresistance.so
	rm /usr/local/bin/electrotest
