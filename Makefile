CXXFLAGS=-std=c++2a -Wall -Wextra -Werror

SRC=$(wildcard src/*.cpp)

all: bin/align

bin/align: $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^
