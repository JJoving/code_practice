#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cstring>

/*class Vector {
 public:
  Vector(int size = 8): data_(NULL), size_(size), capacity_(size * 2) {
    NewCapacity(capacity_);
  }

  void push_back(int num) {
    if(capacity_ == size_) {
      NewCapacity(capacity_ * 2);
    }
    data_[size_++] = num;
  }

  int size() {
    return size_;
  }

  int get_item(int i) {
    return data_[i];
  }

  void set_item(int i, const int value) {
    data_[i] = value;
  }

  int operator [](int i) const {
    return data_[i];
  }

  int &operator [](int i) {
    return data_[i];
  }

 private:
  void NewCapacity(int size) {
    capacity_ = size;
    int *new_vec = new int[size];
    if (data_) {
      memcpy(new_vec, data_, sizeof(int) * size_);
      delete []data_;
    }
    data_ = new_vec;
  }

  int size_;
  int capacity_;
  int *data_;
};
*/

template<class T>
class Vector {
 public:
  Vector(int size = 8): data_(NULL), size_(size), capacity_(size * 2) {
    NewCapacity(capacity_);
  }

  T& push_back(T num) {
    if (capacity_ == size_) {
      NewCapacity(capacity_ * 2);
    }
    data_[size_++] = num;
  }

  T& size() {
    return size_;
  }

  int get_item(int i) {
    return data_[i];
  }

  void set_item(int i, const T& value) {
    data_[i] = value;
  }


  T operator[](int i) const {
    return data_[i];
  }

  T& operator[](int i) {
    return data_[i];
  }

 private:
  void NewCapacity(int size) {
    capacity_ = size;
    T *new_vec = new T[size];
    if (data_) {
      memcpy(new_vec, data_, sizeof(T) * size_);
      delete []data_;
    }
    data_ = new_vec;
  }

  int size_;
  int capacity_;
  T *data_;
};

#endif  //
