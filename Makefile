#!make -f
# Compiler: clang++
CXX=clang++
# Compiler flags -std=c++11: use C++11 standard, -Werror: treat warnings as errors, -Wsign-conversion: warn on sign conversion
# -g: include debugging information in the output file
CXXFLAGS=-std=c++11 -Werror -Wsign-conversion -g
# Valgrind flags -v: verbose, --leak-check=full: check for memory leaks, --show-leak-kinds=all: show all kinds of leaks. 
# --error-exitcode=99: return error code 99 if there are leaks
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

# Source files for test executable
SOURCES_TEST=Graph.cpp Algorithms.cpp TestCounter.cpp Test.cpp
# Object files for test executable
OBJECTS_TEST=$(subst .cpp,.o,$(SOURCES_TEST))

# Source files for demo executable
SOURCES_DEMO=Graph.cpp Algorithms.cpp Demo.cpp
# Object files for demo executable
OBJECTS_DEMO=$(subst .cpp,.o,$(SOURCES_DEMO))

# doctest flags 
DOCTEST_FLAGS=-std=c++11 -I doctest

all: demo test

run: demo
	./$^

demo: Demo.o $(OBJECTS_DEMO)
	$(CXX) $(CXXFLAGS) $^ -o demo

test: TestCounter.o Test.o $(OBJECTS_TEST)
	$(CXX) $(CXXFLAGS) $^ -o test

tidy:
	clang-tidy $(SOURCES_TEST) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

.PHONY: clean all tidy valgrind run

clean:
	rm -f *.o demo test
