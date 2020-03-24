CFLAGS=-Iinclude -Wall -Wextra -Werror
OBJECTS=bin/main.o bin/algorithm.o bin/io.o bin/util.o

all: lab1

bin:
	mkdir bin

lab1: $(OBJECTS)
	gcc $(OBJECTS) -o lab1

bin/main.o: src/main.c include/algorithm.h include/io.h include/util.h | bin
	gcc -o bin/main.o -c $(CFLAGS) src/main.c

bin/algorithm.o: src/algorithm.c include/algorithm.h | bin
	gcc -o bin/algorithm.o -c $(CFLAGS) src/algorithm.c 

bin/io.o: src/io.c include/io.h | bin
	gcc -o bin/io.o -c $(CFLAGS) src/io.c 

bin/util.o: src/util.c include/util.h | bin
	gcc -o bin/util.o -c $(CFLAGS) src/util.c

clean:
	rm -rf bin
	rm -rf lab1
