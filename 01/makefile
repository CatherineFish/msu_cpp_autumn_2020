CC=g++
FLAGS=-std=c++17 -Wall -pedantic -Wextra -Wno-unused-variable

all: alloc_prog

test: alloc_prog
	./alloc_prog

alloc_prog: AllocatorRealisation.o tests.o
	$(CC) $(FLAGS) -o alloc_prog AllocatorRealisation.o tests.o

AllocatorRealisation.o: AllocatorRealisation.cpp Allocator.h
	$(CC) $(FLAGS) -c AllocatorRealisation.cpp

tests.o: tests.cpp Allocator.h
	$(CC) $(FLAGS) -c tests.cpp

clean:
	rm -rf *.o alloc_prog