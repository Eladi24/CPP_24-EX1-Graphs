#!make -f
# Compiler: clang++ (LLVM based)
CXX=g++
# Compiler flags -std=c++11: use C++11 standard, -Werror: treat warnings as errors, -Wsign-conversion: warn on sign conversion
CXXFLAGS=-std=c++11 -Werror -Wsign-conversion
# Valgrind flags -v: verbose, --leak-check=full: check for memory leaks, --show-leak-kinds=all: show all kinds of leaks. 
# --error-exitcode=99: return error code 99 if there are leaks
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

# Source files
SOURCES=Graph.cpp Algorithms.cpp TestCounter.cpp Test.cpp
# Object files
OBJECTS=$(subst .cpp,.o,$(SOURCES))

run: demo
	./$^

demo: Demo.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo

test: TestCounter.o Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test
