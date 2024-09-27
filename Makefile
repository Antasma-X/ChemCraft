CC=clang++
Cflags= -Wall -g --std=c++17 -v
LIB = build/imgui.o

all: main

main: build/element.o build/values.o build/main.o build/compound.o
	$(CC) $(Cflags) -o $@ $^

cute: build/element.o build/values.o build/test.o build/compound.o
	$(CC) $(Cflags) -o $@ $^

build/element.o: src/element.cpp
	$(CC) $(Cflags) -o $@ -c $^

build/values.o: src/values.cpp
	$(CC) $(Cflags) -o $@ -c $^

build/compound.o: src/compound.cpp
	$(CC) $(Cflags) -o $@ -c $^

build/test.o: test/test.cpp
	$(CC) $(Cflags) -o $@ -c $^

build/imgui.o: lib/imgui/src/imgui_demo.cpp lib/imgui/src/imgui_draw.cpp lib/imgui/src/imgui/imgui_impl_glfw.cpp lib/imgui/src/imgui_opengl3.cpp lib/imgui/src/imgui_tables.cpp lib/imgui/src/imgui_widgets.cpp lib/imgui/src/imgui.cpp
	$(CC) $(Cflags) -o $@ -c $^
clean:
	rm build/*.o main cute

test:


