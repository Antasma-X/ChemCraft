CC=g++
Cflags= -Wall -g --std=c++11

all: main


main: executable/main.o executable/values.o
	$(CC) $(Cflags) -o $@ $^

executable/main.o: src/main.cpp
	$(CC) $(Cflags) -o $@ -c $^

executable/values.o: src/values.cpp
	$(CC) $(Cflags) -o $@ -c $^

clean:
	rm *.o

test:


