
EXECUTABLE = sudoku_solver
OBJECTS    = options.o
CXX        = g++
CXXFLAGS   = -O3 -Wall -Wextra -pedantic
VERSION    = 0.2

all: $(EXECUTABLE)

$(EXECUTABLE): main.cpp $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< $(OBJECTS) -o $@

%.o : %.cpp %.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<

.PHONY: tag release clean

tag:
	git tag v$(VERSION) -m "version $(VERSION)"

release:
	git archive --worktree-attributes --format=tar \
	--prefix=sudoku_solver-$(VERSION)/ \
	v$(VERSION) | gzip > sudoku_solver-$(VERSION).tar.gz

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
