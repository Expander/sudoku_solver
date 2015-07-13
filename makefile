
EXECUTABLE  := sudoku_solver
SRCEXT      := cpp
SRC         := $(wildcard *.$(SRCEXT))
OBJECTS     := $(SRC:%.$(SRCEXT)=%.o)
DEPS        := $(SRC:%.$(SRCEXT)=%.d)
CXX         := g++
CXXFLAGS    := -std=c++11 -O3 -Wall -Wextra -pedantic
CXXFLAGSDEP := -std=c++11
VERSION     := 0.3

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
	$(CXX) $(CXXFLAGSDEP) -MM -MP -MG -o $@ $<

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),release)
ifneq ($(MAKECMDGOALS),tag)
-include $(DEPS)
endif
endif
endif

.PHONY: tag release clean

tag:
	git tag v$(VERSION) -m "version $(VERSION)"

release:
	git archive --worktree-attributes --format=tar \
	--prefix=sudoku_solver-$(VERSION)/ \
	v$(VERSION) | gzip > sudoku_solver-$(VERSION).tar.gz

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(DEPS) config.hpp
