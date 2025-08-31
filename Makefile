incdir=/usr/include
libdir=/usr/lib/x86_64-linux-gnu

all: arcfour example

example: example.o
	gcc arcfour.o example.o -o example -Wall -O2

example.o: example.c
	gcc -c -O2 -Wall example.c

arcfour: arcfour.o
	gcc arcfour.o -o libarcfour.so -O2 -Wall -fPIC -shared -ldl -D_GNU_SOURCE

arcfour.o: arcfour.c
	gcc -c -O2 -Wall arcfour.c

clean:
	rm -f *.o *.so example

install:
	cp libarcfour.so ${libdir}
	cp arcfour.h ${incdir}
	ldconfig

