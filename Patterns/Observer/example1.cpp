#include "Subject.h"   // Our Subject class
#include "EventType.h" // Our EventType enumeration
#include <functional>  // for std::function and std::bind
#include <iostream>

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

  Subject<EventType> s;
  s.registerObserver(EventType::GREEN, bar);
  s.registerObserver(EventType::ORANGE, std::bind(foo, 42));
  s.registerObserver(EventType::RED, std::bind(foo, 12345));

  s.notify(EventType::GREEN);
  s.notify(EventType::RED);
  s.notify(EventType::ORANGE);

}

