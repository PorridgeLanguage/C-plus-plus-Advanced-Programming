#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <cstring>
#include <iostream>
#include <optional>

// TODO: 在这里编写你的ArrayList类
template <typename T>
class ArrayList {
 private:
  T* data;
  int size;
  int capacity;

  void expand_capacity() {
    int new_capacity = capacity + (capacity >> 1);
    T* new_data = new T[new_capacity];
    for (int i = 0; i < size; i++) {
      new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
  }

 public:
  ArrayList()
      : size(0), capacity(10) {
    data = new T[capacity];
  }

  ~ArrayList() {
    delete[] data;
  }

  void add(const T& x) {
    if (size == capacity) {
      expand_capacity();
    }
    data[size] = x;
    size++;
  }

  void remove(const T& x) {
    for (int i = 0; i < size; i++) {
      if (data[i] == x) {
        for (int j = i; j < size - 1; j++) {
          data[j] = data[j + 1];
        }
        size--;
        break;
      }
    }
  }

  std::optional<T> get(int index) const {
    if (index < 0 || index >= size) {
      return std::nullopt;
    }
    return data[index];
  }

  int getSize() {
    return size;
  }

  int getCapacity() const {
    return capacity;
  }
};

#endif  // ARRAYLIST_H