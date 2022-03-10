SRC=$(wildcard src/*.cpp)

all: bin/align

bin/align: $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^
