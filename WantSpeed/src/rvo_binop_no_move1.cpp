#include <iostream>
#include "Bar_no_move.h"
#include "Foo_no_move.h"


void foo()
{
  std::cout << "========== Foo ==============\n";

  Foo a, b;

  Foo c = a + b;

  std::cout << "=============================\n";

}


void bar()
{
  std::cout << "========== Bar ==============\n";

  Bar a, b;

  Bar c = a + b;

  std::cout << "=============================\n";

}

int main()
{
  foo();
  bar();
}
