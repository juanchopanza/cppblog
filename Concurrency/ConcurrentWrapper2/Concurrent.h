///
/// A concurrent wrapper for serializing asynchronous access to a shared resource.
/// This is a working version of the concurrent<T> class presented in this excellent presentation 
/// on C++ concurrency by Herb Sutter:
/// http://channel9.msdn.com/Shows/Going+Deep/C-and-Beyond-2012-Herb-Sutter-Concurrency-and-Parallelism
///
/// This is an extension of the concurrent wrapper presented in this blog:
/// http://juanchopanzacpp.wordpress.com/2013/03/01/concurrent-object-wrapper-c11/ 
///
/// Currently does not compile on gcc 4.7 or 4.8 due to a compiler bug related 
/// to decltype of member variables used in a trailing return type.
/// This is expected to be fixed in GCC 4.8.1.
///
/// Wraps a shared resource such that callers can request operations on the resource asynchronously.
/// Each request is treated as an atomic transaction, and the caller side is not blocked.
///
/// Internally uses concurrent queue developed for the concurrent queue blog
/// http://juanchopanzacpp.wordpress.com/2013/02/26/concurrent-queue-c11/
///
/// Example useage:
///
/// @code
/// Concurrent<std::vector<int>> cv;
///
/// //1: Resize the vector, fill with sequence
/// auto f1 = cv([](std::vector<int>& v)->size_t{ v.resize(10);
///                                               std::iota(v.begin(), v.end(), 0);
///                                               return v.size();
///                                              });
///
/// //2. Calculate the sum of elements
/// auto f2 = cv([](const std::vector<int>& v){ return std::accumulate(v.begin(), v.end(), 0);});
/// 
/// //3: Call some user defined functions
/// int foo(std::vector<int>& v);
/// void bar(std::vector<int>& v);
/// // run bar, then foo on the shared resource
/// auto f3 = cs([] (std::vector<int>& v)->int { bar(v); 
///                                              return foo(v);
///                                            });
///
/// //4 get the results when needed
/// std::cout << f1.get() << " " << f2.get() " " << f3.get() << std::endl;
///

#include <functional>
#include <thread>
#include <future>
#include <exception>
#include "Queue/Queue.h"

template <typename T>
class Concurrent
{
 public:

  Concurrent(T resource = T{}) 
  : 
  resource_{resource},
  done_{false}
  {
    worker_ = std::thread([this]{ while (!done_) queue_.pop()();} );
  }

  ~Concurrent()
  {
    queue_.push([this]{done_ = true;});
    worker_.join();
  }

  template <typename F>
  auto operator()(F f) const -> std::future<decltype(f(resource_))>
  {
    auto prom = std::make_shared<std::promise<decltype(f(resource_))>>();
    auto fut = prom->get_future();     
    queue_.push([=]{
                     try { prom->set_value(f(resource_)); }
                     catch(...) { prom->set_exception(std::current_exception()); }
                   }
               );
    return fut;
  }

 private:

  mutable Queue<std::function<void()>> queue_;
  mutable T resource_;
  std::thread worker_;
  bool done_;

};
