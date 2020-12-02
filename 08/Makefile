CXX ?= g++
CXXFLAGS += -std=c++17 -pthread -Wall -pedantic -Werror -Wextra -Wno-unused-variable -g
PROG ?= prog
OBJ := test.o

all: $(PROG)

test: all
	./$(PROG)

$(PROG): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LDFLAGS) -o $@

clean:
	rm -rf $(OBJ) $(PROG)

test.o: ThreadPool.h ThreadPool.tpp

.PHONY: clean test all