#include "Subject.h"   // Our Subject class
#include <functional>  // for std::function and std::bind
#include <iostream>
#include <string>

void foo(int i)
{
  std::cout << "foo( " <<  i << " )\n";
}

void bar() 
{
  std::cout << "bar()\n";
}

int main()
{

  Subject<std::string> s;
  s.registerObserver("GREEN", bar);
  s.registerObserver("ORANGE", std::bind(foo, 42));
  s.registerObserver("RED", std::bind(foo, 12345));
  const std::string msg("Hello, RED!");
  s.registerObserver("RED", [&msg]{std::cout << msg << std::endl;});

  s.notify("GREEN");
  s.notify("RED");
  s.notify("ORANGE");

}

