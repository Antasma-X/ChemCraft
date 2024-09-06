CC=clang++
Cflags= -Wall -g --std=c++11

all: main


main: build/element.o build/values.o build/test.o
	$(CC) $(Cflags) -o $@ $^

build/element.o: src/element.cpp
	$(CC) $(Cflags) -o $@ -c $^

build/values.o: src/values.cpp
	$(CC) $(Cflags) -o $@ -c $^

build/compound.o: src/compound.cpp
	$(CC) $(Cflags) -o $@ -c $^

build/test.o: src/test.cpp
	$(CC) $(Cflags) -o $@ -c $^

clean:
	rm build/*.o main

test:


