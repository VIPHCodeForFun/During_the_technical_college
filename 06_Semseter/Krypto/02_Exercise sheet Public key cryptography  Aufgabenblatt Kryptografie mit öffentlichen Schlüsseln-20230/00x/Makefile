CXX ?= g++
CXXFLAGS += -c -Wall -Wextra -Werror
LDFLAGS += -lgmpxx -lgmp

SRC = $(wildcard *.cpp)
HDR = $(wildcard *.h)
OBJ = $(SRC:.cpp=.o)

all: Release

Debug: CXXFLAGS += -g
Debug: test

Release: test

test: $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp $(HDR)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(OBJ) test
