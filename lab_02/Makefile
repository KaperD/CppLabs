CFLAGS=-Iinclude -Wall -Wextra -Werror
OBJECTS=obj/str.o obj/test.o obj/test_str.o

all: lab_02

obj:
	mkdir obj

lab_02: $(OBJECTS)
	gcc $(OBJECTS) -o lab_02

obj/str.o: src/str.c | obj
	gcc -c $(CFLAGS) src/str.c -o obj/str.o 

obj/test.o: src/test.c include/test_str.h include/str.h | obj
	gcc -c $(CFLAGS) src/test.c -o obj/test.o 

obj/test_str.o: src/test_str.c include/str.h | obj
	gcc -c $(CFLAGS) src/test_str.c -o obj/test_str.o 

clean:
	rm -rf obj
	rm -rf lab_02
