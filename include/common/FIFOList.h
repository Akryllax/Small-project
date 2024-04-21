#include <list>
#include <string>

template <typename T>
class FIFOList {
private:
  std::list<T> data;

public:
  using const_iterator = typename std::list<T>::const_iterator;

  // This allows you to iterate over the elements
  typename std::list<T>::const_iterator begin() {
    return data.begin();
  }

  typename std::list<T>::const_iterator end() {
    return data.end();
  }

  void push(const T& value) {
    data.push_back(value);
  }

  void pop() {
    if (!data.empty()) {
      data.pop_front();
    }
  }

  T& front() {
    return data.front();
  }

  const T& front() const {
    return data.front();
  }

  bool empty() const {
    return data.empty();
  }

  size_t size() const {
    return data.size();
  }
};