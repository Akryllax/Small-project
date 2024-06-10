#include <list>
#include <string>

template <typename T>
class FILOList {
private:
  std::list<T> data;

public:
  // This allows you to iterate over the elements
  typename std::list<T>::const_iterator begin() {
    return data.begin();
  }

  typename std::list<T>::const_iterator end() {
    return data.end();
  }

  void push(const T& value) {
    data.push_front(value);
  }

  void pop() {
    if (!data.empty()) {
      data.pop_front();
    }
  }

  T& top() {
    return data.front();
  }

  const T& top() const {
    return data.front();
  }

  bool empty() const {
    return data.empty();
  }
};