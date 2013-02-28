#include <functional>
#include <thread>
#include "Queue/Queue.h"

template <typename T>
class ConcurrentWrapper
{
 public:

  ConcurrentWrapper(T resource = T{}) 
  : 
  resource_{resource},
  done_{false}
  {
    worker_ = std::thread([this]{ while (!done_) queue_.pop()();} );
  }

  ~ConcurrentWrapper()
  {
    queue_.push([this]{done_ = true;});
    worker_.join();
  }

  template <typename F>
  void operator()(F f) const
  { 
    queue_.push([=]{f(resource_);});
  }

 private:

  mutable Queue<std::function<void()>> queue_;
  mutable T resource_;
  std::thread worker_;
  bool done_;

};
