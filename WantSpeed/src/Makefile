CXXFLAGS += -Wall -Wextra -Wconversion -Wno-missing-field-initializers -pedantic-errors -std=c++11  -O2

case%_no_move : case%_no_move.cpp Bar_no_move.h Foo_no_move.h Makefile
	$(CXX) $(CXXFLAGS) $<  -o $@ 

case% : case%.cpp Bar.h Foo.h Makefile
	$(CXX) $(CXXFLAGS) $<  -o $@ 

