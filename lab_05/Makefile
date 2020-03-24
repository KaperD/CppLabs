CFLAGS=-Iinclude -Wall -Wextra -Werror

all: lab_05

obj:
	mkdir obj

lab_05: obj/main.o obj/clist.o obj/point_list.o
	gcc obj/main.o obj/clist.o obj/point_list.o -o lab_05

obj/main.o: src/main.c include/point_list.h include/clist.h | obj	
	gcc -c $(CFLAGS) src/main.c -o obj/main.o

obj/clist.o: src/clist.c include/clist.h | obj
	gcc -c $(CFLAGS) src/clist.c -o obj/clist.o

obj/point_list.o: src/point_list.c include/point_list.h | obj
	gcc -c $(CFLAGS) src/point_list.c -o obj/point_list.o

clean:
	rm -rf *.txt
	rm -rf *.bin
	rm -rf obj
	rm -rf lab_05