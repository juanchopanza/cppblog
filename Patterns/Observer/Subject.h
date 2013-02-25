#ifndef SUBJECT_H_
#define SUBJECT_H_

#include <functional>
#include <map>
#include <vector>

template <typename Event>
class Subject
{
 public:
  Subject()=default;
  template <typename Observer>
  void registerObserver(const Event& event, const Observer& observer)
  {
    observers_[event].push_back(observer);
  }
  void notify(const Event& event) const
  {
    for (const auto& obs : observers_.at(event)) obs();
  }
  // disallow copying and assigning
  Subject(const Subject&)=delete;
  Subject& operator=(const Subject&)=delete;

 private:
  std::map<Event, std::vector<std::function<void()>>> observers_;
};

#endif // SUBJECT_H_
