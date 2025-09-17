#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T, std::size_t N>
class array {
public:
  using value_type = T;
  using size_type = std::size_t;
  using reference = T&;
  using const_reference = const T&;
  using pointer = T*;
  using const_pointer = const T*;
  using iterator = T*;
  using const_iterator = const T*;

  // capacity
  constexpr size_type size() const noexcept {return N;}
  constexpr bool empty() const noexcept {return N == 0;}
 
  // access
  reference operator[](size_type i) {return elems[i];}
  const_reference operator[](size_type i) const {return elems[i];}
  reference at(size_type i) {
    if (i >= N) {
      throw std::out_of_range("index is out of range");
    }
    return elems[i];
  }
  const_reference at(size_type i) const {
    if (i >= N) {
      throw std::out_of_range("index is out of range");
    }
    return elems[i];
  }
  reference front() {return elems[0];}
  const_reference front() const {return elems[0];}
  reference back() {return elems[N-1];}
  const_reference back() const {return elems[N-1];}
  T* data() noexcept {return elems;}
  const T* data() const noexcept {return elems;} 

  // iterators
  iterator begin() noexcept { return elems;}
  const_iterator begin() const noexcept {return elems;}
  iterator end() noexcept {return elems + N;}
  const_iterator end() const noexcept {return elems + N;}

  // modifiers
  void fill(const T& value) {
    for (size_type i = 0;i < N; ++i) {
      elems[i] = value;
    }
  }
  void swap(array& other) noexcept {
    for (size_type i = 0;i < N; ++i) {
      std::swap(elems[i], other.elems[i]);
    }
  }

private:
  T elems[N];

};
