#include <iostream>
#include "Bar_no_move.h"
#include "Foo_no_move.h"


void foo()
{
  std::cout << "========== Foo ==============\n";

  Foo f = Foo() + Foo() + Foo();

  std::cout << "=============================\n";

}


void bar()
{
  std::cout << "========== Bar ==============\n";

  Bar b = Bar() + Bar() + Bar();

  std::cout << "=============================\n";

}

int main()
{
  foo();
  bar();
}
