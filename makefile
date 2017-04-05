all: program programGTK

program: lib
	gcc -L./lib -Wall -o electrotest main.c -lresistance -lpower -lcomponent -Wl,-rpath=./lib

programGTK: lib
	gcc -L./lib -Wall -o electrotestgtk maingtk.c electrolibui.c `pkg-config --cflags --libs gtk+-3.0` -lresistance -lpower -lcomponent -Wl,-rpath=./lib

libInstall: lib
	sudo cp lib/libresistance.so /usr/lib/libresistance.so
	sudo cp lib/libpower.so /usr/lib/libpower.so
	sudo cp lib/libcomponent.so /usr/lib/libcomponent.so

lib: libresistance.o libpower.o libcomponent.o
	gcc -shared -fPIC -o lib/libresistance.so libresistance.o
	gcc -shared -fPIC -o lib/libpower.so libpower.o
	gcc -shared -fPIC -o lib/libcomponent.so libcomponent.o

libresistance.o: lib/libresistance/libresistance.c lib/libresistance/libresistance.h
	gcc -c -fPIC lib/libresistance/libresistance.c lib/libresistance/libresistance.h

libpower.o: lib/libpower/libpower.c lib/libpower/libpower.h
	gcc -c -fPIC lib/libpower/libpower.c lib/libpower/libpower.h

libcomponent.o: lib/libcomponent/libcomponent.c lib/libcomponent/libcomponent.h
	gcc -c -fPIC lib/libcomponent/libcomponent.c lib/libcomponent/libcomponent.h

clean:
	rm *.o
	rm lib/*.so
	rm electrotest

install: libInstall
	gcc -Wall -o electrotest main.c -lresistance -lpower -lcomponent
	sudo cp electrotest /usr/local/bin/electrotest

uninstall:
	sudo rm /usr/lib/libresistance.so
	sudo rm /usr/lib/libpower.so
	sudo rm /usr/lib/libcomponent.so
	sudo rm /usr/local/bin/electrotest
