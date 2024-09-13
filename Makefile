CC=g++
Cflags= -Wall -g --std=c++17

all: main

main: build/element.o build/values.o build/main.o
	$(CC) $(Cflags) -o $@ $^

cute: build/element.o build/values.o build/test.o
	$(CC) $(Cflags) -o $@ $^

build/element.o: src/element.cpp
	$(CC) $(Cflags) -o $@ -c $^

build/values.o: src/values.cpp
	$(CC) $(Cflags) -o $@ -c $^

build/compound.o: src/compound.cpp
	$(CC) $(Cflags) -o $@ -c $^

build/test.o: test/test.cpp
	$(CC) $(Cflags) -o $@ -c $^

clean:
	rm build/*.o main 

test:


