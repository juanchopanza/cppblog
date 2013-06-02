#include <vector>
#include <iostream>
#include "Concurrent.h"
#include <vector>
#include <future>
#include <algorithm>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
  os << "[ ";
  for (const auto& i : v) os << i << " ";
  return os << "]";
}

int main()
{
  Concurrent<std::vector<int>> cv{std::vector<int>(10)};
  auto f1 = cv([](std::vector<int>& v){
                 return std::accumulate(v.begin(), v.end(), 0);
               });

  auto f2 = cv([](std::vector<int>& v)->bool{
                 std::iota(v.begin(), v.end(), 0);
                 return true;
               });
  auto f3 = cv([](std::vector<int>& v){
                 return std::accumulate(v.begin(), v.end(), 0);
               });

  auto f4 = cv([](std::vector<int>& v){
                 return v.size();
               });

  auto f5 = cv([](std::vector<int>&){});

  std::cout << std::boolalpha;
  std::cout << f1.get() << std::endl;
  std::cout << f2.get() << std::endl;
  std::cout << f3.get() << std::endl;
  std::cout << f4.get() << std::endl;


}

