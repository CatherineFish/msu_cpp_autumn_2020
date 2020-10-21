CXX ?= g++
CXXFLAGS += -std=c++17 -Wall -pedantic -Wextra -Wno-unused-variable
PROG ?= prog
OBJ := Test_All.o DefaultFunc.o TestFunc.o TokenParser.o

all: $(PROG)

test: all
	./$(PROG)

$(PROG): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LDFLAGS) -o $@

clean:
	rm -rf $(OBJ) $(PROG)

Test_All.o: TokenParser.h
TokenParser.o: TokenParser.h
DefaultFunc.o: DefaultFunc.h
TestFunc.o: TestFunc.h

.PHONY: clean test all