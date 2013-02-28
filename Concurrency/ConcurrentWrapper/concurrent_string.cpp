#include <string>
#include <iostream>
#include "ConcurrentWrapper.h"
#include <vector>
#include <future>

int main()
{
  ConcurrentWrapper<std::string> cs{"Start\n"};

  std::vector<std::future<void>> v;

  for (int i = 0; i < 5; ++i)
  {
    v.push_back(
        std::async(std::launch::async,
                   [&,i] {
                     cs([&i](std::string& s) {
                          s += std::to_string(i) + std::to_string(i)+ std::to_string(i) ;
                          s += "\n";
                     });
                     cs([](const std::string& s) { std::cout << s;});
                   }
                  )
               );
  }

  for (auto& fut : v) fut.wait();
  std::cout << "Done\n";

}

