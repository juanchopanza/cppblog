#include <string>
#include <iostream>
#include "ConcurrentWrapper.h"
#include <vector>
#include <future>
#include <cctype>

void uppercase(char& c)
{
  c = static_cast<char>(std::toupper(c));
}

void lowercase(char& c)
{
  c = static_cast<char>(std::tolower(c));
}


int main()
{
  ConcurrentWrapper<std::string> cs{"QqWwEeRrTtYyUuIiOoPpAaSsDdFfGgHhJjKkLl\n"};

  std::vector<std::future<void>> v1;
  std::vector<std::future<void>> v2;
  std::vector<std::future<void>> v3;

  for (int i = 0; i < 5; ++i)
  {
    v1.push_back(
        std::async(std::launch::async,
                   [&cs,i] {
                     cs([&i](std::string& s) {
                        for (auto& c : s) uppercase(c);
                        });
                     cs([](const std::string& s) { std::cout << s;});
                   }
                  )
               );
    v2.push_back(
        std::async(std::launch::async,
                   [&cs,i] {
                     cs([&i](std::string& s) {
                        for (auto& c : s) lowercase(c);
                        });
                     cs([](const std::string& s) { std::cout << s;});
                   }
                  )
               );

  }

  for (auto& fut : v1) fut.wait();
  for (auto& fut : v2) fut.wait();
  std::cout << "Done\n";

}

