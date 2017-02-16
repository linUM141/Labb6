CC = gcc
OBJECTS = libcomponent.o
INSTALLPATH = /usr/local/bin
LIBRARY = libcomponent.so


all: lib

program: lib
	$(CC) -L. -Wall -o test_main test_libcomponent.c -lcomponent -Wl,-rpath=.

lib: libcomponent.o
	$(CC) -shared -fPIC -o $(LIBRARY) $(OBJECTS)

libcomponent.o: libcomponent.c libcomponent.h
	$(CC) -c -fPIC libcomponent.c libcomponent.h
       	#$(CC) -c -fPIC -mfpmath='387' libcomponent.c libcomponent.h

clean:
	rm $(OBJECTS)
	rm $(LIBRARY)
	rm test_main

test: program
	./test_main
	make clean

install: lib
	cp libcomponent.so $(INSTALLPATH)/$(LIBRARY)

uninstall:
	rm $(INSTALLPATH)/$(LIBRARY)

