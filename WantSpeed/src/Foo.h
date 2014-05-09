#include <iostream>

struct Foo
{
  Foo() { std::cout << "Default constructor\n"; }
  ~Foo() { std::cout << "Destructor\n"; }
  Foo(const Foo&) 
  { 
    std::cout << "Copy constructor\n"; 
  }
  Foo(Foo&&) 
  { 
    std::cout << "Move copy constructor\n"; 
  }
  Foo& operator=(const Foo&) 
  { 
    std::cout << "Assignment operator";
    return *this;
  }
  Foo& operator=(Foo&&) 
  { 
    std::cout << "Move assignment operator\n"; 
    return *this;
  }

  Foo& operator+=(const Foo&)
  {
    return *this;
  }
};


Foo operator+(const Foo& lhs, const Foo& rhs)
{
  Foo res = lhs;
  res += rhs;
  return res;
}

