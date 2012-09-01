
EXECUTABLE = sudoku_solver
SRCEXT     = cpp
SRC        = $(wildcard *.$(SRCEXT))
OBJECTS    = $(SRC:%.$(SRCEXT)=%.o)
DEPS       = $(SRC:%.$(SRCEXT)=%.d)
CXX        = g++
CXXFLAGS   = -O3 -Wall -Wextra -pedantic
VERSION    = 0.2

$(EXECUTABLE): $(OBJECTS)
	$(CXX) -o $@ $^

config.hpp: makefile
	rm -f $@-t $@
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  echo ''; \
	  echo '/* program version */'; \
	  echo '#define VERSION "$(VERSION)"'; \
	} | sed '/""/d' > $@-t
	mv $@-t $@

%.d: %.$(SRCEXT)
	$(CXX) -MM -MP -MG -o $@ $<

-include $(DEPS)

.PHONY: tag release clean

tag:
	git tag v$(VERSION) -m "version $(VERSION)"

release:
	git archive --worktree-attributes --format=tar \
	--prefix=sudoku_solver-$(VERSION)/ \
	v$(VERSION) | gzip > sudoku_solver-$(VERSION).tar.gz

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(DEPS) config.hpp
