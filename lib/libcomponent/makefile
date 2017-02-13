CC = gcc
OBJECTS = libcomponent.o
INSTALLPATH = /usr/local\bin
LIBRARY = libcomponent.so


all: lib

#program: lib
#	$(CC) -L. -Wall -o test_main test_main.c -lresistance -Wl,-rpath=.

lib: libcomponent.o
	$(CC) -shared -fPIC -o $(LIBRARY) $(OBJECTS)

libcomponent.o: libcomponent.c libcomponent.h
	$(CC) -c -fPIC libresistance.c libresistance.h

clean:
	rm $(OBJECTS)
	rm $(LIBRARY)

#test: program
#	./test_main

install: lib
	cp libresistance.so $(INSTALLPATH)/$(LIBRARY)
	clean

uninstall:
	rm $(INSTALLPATH)/$(LIBRARY)

