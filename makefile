all: program

program: lib
	gcc -L./lib -Wall -o electrotest main.c -lresistance -lcomponent -Wl,-rpath=./lib

libInstall: lib
	sudo cp lib/libresistance.so /usr/lib/libresistance.so
	sudo cp lib/libcomponent.so /usr/lib/libcomponent.so

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

install: libInstall
	gcc -Wall -o electrotest main.c -lresistance -lcomponent
	sudo cp electrotest /usr/local/bin/electrotest

uninstall:
	sudo rm /usr/lib/libresistance.so
	sudo rm /usr/lib/libcomponent.so
	sudo rm /usr/local/bin/electrotest
