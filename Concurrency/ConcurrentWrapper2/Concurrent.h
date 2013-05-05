///
/// A concurrent wrapper for serializing asynchronous access to a shared resource.
/// This is a working version of the concurrent<T> class presented in this excellent presentation 
/// on C++ concurrency by Herb Sutter:
/// http://channel9.msdn.com/Shows/Going+Deep/C-and-Beyond-2012-Herb-Sutter-Concurrency-and-Parallelism
///
/// Tweaked to compile with g++ 4.7.2.
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
/// Concurrent<std::string> cs;
///
/// //Thread 1: just print the string
/// cs([](const std::string& s){ std::cout << s;});
/// 
/// // Thread 2:
/// void foo(std::string& s);
/// void bar(std::string& s);
/// // run bar, then foo on the shared resource
/// cs([] (std::string& s) { bar(s); foo(s);});
///
/// // Thread 3: make string uppercase
/// cs([](std::string& s){ for (auto& c : s) c = static_cast<char>(std::toupper(c));)} );
///
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
