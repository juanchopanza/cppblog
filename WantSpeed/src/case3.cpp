#include <iostream>
#include "Bar.h"
#include "Foo.h"


void foo()
{
  std::cout << "========== Foo ==============\n";

  Foo foo = Foo() + Foo();

  std::cout << "=============================\n";

}


void bar()
{
  std::cout << "========== Bar ==============\n";

  Bar b = Bar() + Bar();

  std::cout << "=============================\n";

}

int main()
{
  foo();
  bar();
}
