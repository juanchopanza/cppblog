#include <iostream>

struct Bar
{
  Bar() { std::cout << "Default constructor\n"; }
  ~Bar() { std::cout << "Destructor\n"; }
  Bar(const Bar&) 
  { 
    std::cout << "Copy constructor\n"; 
  }
  
  Bar& operator=(const Bar&) 
  { 
    std::cout << "Assignment operator";
    return *this;
  }

  Bar& operator+=(const Bar&)
  {
    return *this;
  }
};


Bar operator+(Bar lhs, const Bar& rhs)
{
  lhs += rhs;
  return lhs;
}

