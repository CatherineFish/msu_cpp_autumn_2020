CXX ?= g++
CXXFLAGS += -std=c++17 -Wall -pedantic -Wextra -Wno-unused-variable
PROG ?= prog
OBJ := BigInt.o test.o

all: $(PROG)

test: all
	./$(PROG)

$(PROG): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LDFLAGS) -o $@

clean:
	rm -rf $(OBJ) $(PROG)

BigInt.o: BigInt.h
test.o: BigInt.h

.PHONY: clean test all