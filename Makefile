CC=g++
Cflags= -Wall -g --std=c++17 -fsanitize=address
LIB = build/imgui.o
TEST=-lgtest -lgtest_main -lpthread
all: main

main: build/element.o build/values.o build/main.o build/compound.o build/molecules.o
	$(CC) $(Cflags) -o $@ $^

cute: build/element.o build/values.o build/test.o build/compound.o build/molecules.o
	$(CC) $(Cflags) -o $@ $^

build/element.o: src/element.cpp
	$(CC) $(Cflags) -o $@ -c $^

build/values.o: src/values.cpp
	$(CC) $(Cflags) -o $@ -c $^

build/compound.o: src/compound.cpp
	$(CC) $(Cflags) -o $@ -c $^

build/test.o: test/test.cpp
	$(CC) $(Cflags) $(TEST) -o $@ -c $^

build/molecules.o: src/molecules.cpp
	$(CC) $(Cflags) -o $@ -c $^

window: build/imgui.o build/window.o
	$(CC) $(Cflags) -o $@ $^

build/window.o: src/window.cpp
	$(CC) $(Cflags) -o $@ -c $^

clean:
	rm build/*.o main cute

build/imgui.o: build/imgui_demo.o build/imgui_draw.o  build/imgui_tables.o build/imgui_widgets.o build/imgui.o
	$(CC) $(Cflags) -o $@ -c $^

build/imgui_demo.o: lib/imgui/src/imgui_demo.cpp
	$(CC) $(Cflags) -o $@ -c $^

build/imgui_draw.o: lib/imgui/src/imgui_draw.cpp
	$(CC) $(Cflags) -o $@ -c $^

build/imgui_tables.o: lib/imgui/src/imgui_tables.cpp
	$(CC) $(Cflags) -o $@ -c $^

build/imgui_widgets.o: lib/imgui/src/imgui_widgets.cpp
	$(CC) $(Cflags) -o $@ -c $^

build/imgui.o: lib/imgui/src/imgui.cpp
	$(CC) $(Cflags) -o $@ -c $^