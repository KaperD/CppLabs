CFLAGS=-Iinclude -Wall -Wextra -Werror

all: hw_01

obj:
	mkdir obj

hw_01: obj/main.o obj/bmp.o
	gcc obj/main.o obj/bmp.o -o hw_01

obj/main.o: src/main.c include/bmp.h | obj
	gcc -c $(CFLAGS) src/main.c -o obj/main.o

obj/bmp.o: src/bmp.c include/bmp.h | obj
	gcc -c $(CFLAGS) src/bmp.c -o obj/bmp.o

clean:
	rm -rf obj
	rm -rf hw_01
