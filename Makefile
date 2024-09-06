CC=clang++
Cflags= -Wall -g --std=c++11

all: main


main: build/main.o build/values.o
	$(CC) $(Cflags) -o $@ $^

build/main.o: src/main.cpp
	$(CC) $(Cflags) -o $@ -c $^

build/values.o: src/values.cpp
	$(CC) $(Cflags) -o $@ -c $^

clean:
	rm build/*.o

test:


