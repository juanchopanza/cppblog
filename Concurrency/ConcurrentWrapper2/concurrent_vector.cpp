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
  Concurrent<std::vector<int>> cv{{1, 2, 3, 4, 5, 6}};

  auto f1 = cv([](std::vector<int>& v){
                 return std::accumulate(v.begin(), v.end(), 0);
               });
  std::cout << f1.get() << std::endl;

}

