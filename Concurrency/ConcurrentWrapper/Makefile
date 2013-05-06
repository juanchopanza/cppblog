CXX := /usr/bin/g++-4.7
#CXX := clang++
CPPFLAGS := -I..
CXXFLAGS := -Wall -Wextra -pedantic-errors -std=c++11 -O2 -pthread

DEPS = ConcurrentWrapper.h ../Queue/Queue.h

% : %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $< -o $@
