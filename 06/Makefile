CXX ?= g++
CXXFLAGS += -std=c++17 -Wall -pedantic -Wextra -Wno-unused-variable
PROG ?= prog
OBJ := test.o

all: $(PROG)

test: all
	./$(PROG)

$(PROG): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LDFLAGS) -o $@

clean:
	rm -rf $(OBJ) $(PROG)

test.o: Format.h Format.tpp

.PHONY: clean test all