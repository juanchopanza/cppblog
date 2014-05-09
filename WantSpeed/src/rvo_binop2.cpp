#include <iostream>
#include "Bar.h"
#include "Foo.h"


void foo()
{
  std::cout << "========== Foo ==============\n";

  Foo a, b, c;

  Foo d = a + b + c;

  std::cout << "=============================\n";

}


void bar()
{
  std::cout << "========== Bar ==============\n";

  Bar a, b, c;

  Bar d = a + b + c;

  std::cout << "=============================\n";

}

int main()
{
  foo();
  bar();
}
