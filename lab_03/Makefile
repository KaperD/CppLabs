CFLAGS=-Iinclude -Wall -Wextra -Werror

all: lab_03

obj: 
	mkdir obj

lab_03: obj/main.o obj/clist.o
	gcc obj/main.o obj/clist.o -o lab_03

obj/main.o: src/main.c include/clist.h | obj
	gcc -c $(CFLAGS) src/main.c -o obj/main.o 

obj/clist.o: src/clist.c include/clist.h | obj
	gcc -c $(CFLAGS) src/clist.c -o obj/clist.o

clean:
	rm -rf obj
	rm -rf lab_03