#include "MyContainer.h"

int MyContainer::_count = 0;

MyContainer::MyContainer(int size)
    : _size(size) {
  _data = new int[_size];
  ++_count;
}

MyContainer::~MyContainer() {
  delete[] _data;
  --_count;
}

MyContainer::MyContainer(const MyContainer& Other)
    : _size(Other._size) {
  _data = new int[_size];
  std::copy(Other._data, Other._data + _size, _data);
  ++_count;
}

MyContainer& MyContainer::operator=(const MyContainer& Other) {
  if (this != &Other) {
    delete[] _data;
    _size = Other._size;
    _data = new int[_size];
    std::copy(Other._data, Other._data + _size, _data);
  }
  return *this;
}

int MyContainer::size() const {
  return _size;
}

int* MyContainer::data() const {
  return _data;
}

int MyContainer::count() {
  return _count;
}