CXX ?= g++
CXXFLAGS += -std=c++17 -Wall -pedantic -Wextra -Wno-unused-variable
PROG ?= prog
OBJ := Matrix.o test.o

all: $(PROG)

test: all
	./$(PROG)

$(PROG): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LDFLAGS) -o $@

clean:
	rm -rf $(OBJ) $(PROG) result.txt

Matrix.o: Matrix.h
test.o: Matrix.h

.PHONY: clean test all