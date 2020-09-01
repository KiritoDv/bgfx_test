CC = g++

BGFX_DIR = /home/alucherdi/lj/bgfx/bgfx/.build/linux64_gcc/bin/libbgfx-shared-libRelease.so
BGFX_HEADERS =  -Ibgfx/include -Ibx/include -Ibimg/include

COMPILER_FLAGS = -w -std=c++11
LINKER_FLAGS = $(BGFX_DIR) -lSDL2 -lGL -lX11 -lpthread

main : main.o core.o
	$(CC) main.o core.o -o main $(COMPILER_FLAGS) $(LINKER_FLAGS) $(BGFX_HEADERS)

core.o: core/core.cpp
	$(CC) -c core/core.cpp

main.o: main.cpp
	$(CC) -c main.cpp
