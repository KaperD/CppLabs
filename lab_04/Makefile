CFLAGS=-Iinclude -Wall -Wextra -Werror

all: lab_04

obj: 
	mkdir obj

lab_04: obj/main.o obj/mergesort.o
	gcc obj/main.o obj/mergesort.o -o lab_04 

obj/main.o: src/main.c include/mergesort.h | obj
	gcc -c $(CFLAGS) src/main.c -o obj/main.o 

obj/mergesort.o: src/mergesort.c include/mergesort.h | obj
	gcc -c $(CFLAGS) src/mergesort.c -o obj/mergesort.o 

clean:
	rm -rf obj
	rm -rf lab_04
