
EXECUTABLE = sudoku_solver
OBJECTS    = options.o
CXX        = g++
CXXFLAGS   = -O3 -Wall -Wextra -pedantic

all: $(EXECUTABLE)

$(EXECUTABLE): main.cpp $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< $(OBJECTS) -o $@

%.o : %.cpp %.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
