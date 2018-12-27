CXX = g++
CXXFLAGS = -g

OBJ = fst.o

fst_main: main.cc $(OBJ)
	$(CXX) $< $(OBJ) -o $@ $(CXXFLAGS)

%.o: %.cc
	$(CXX) -c $< -o $@ $(CXXFLAGS)


.PHONY: clean
clean:
	rm fst_main
