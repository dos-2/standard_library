#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <memory>
#include <algorithm>

template <typename T>
class vector {
public:
  using value_type = T;
  using size_type = std::size_t;
  using reference = T&;
  using const_reference = const T&;
  using pointer = T*;
  using const_pointer = const T*;
  using iterator = T*;
  using const_iterator = const T*;

  vector() noexcept = default;
  explicit vector(size_type count) : sz(count), cap(count), elems(alloc.allocate(count)) {
    for (int i = 0;i < sz;++i) {
      std::construct_at(elems + i);
    }
  }
  ~vector() {
    clear();
    if (elems) {
      alloc.deallocate(elems, cap);
    }
  }

  void clear() noexcept {
    for (size_type i = 0;i < sz;++i) {
      std::destroy_at(elems + i);
    }
    sz = 0;
  }
 
  reference operator[](size_type i) noexcept {
    return elems[i];
  }

  const_reference operator[](size_type i) const noexcept {
    return elems[i];
  }

  size_type size() const noexcept {return sz;}
  size_type capacity() const noexcept {return cap;}
  bool empty() const noexcept {return sz == 0;}

  void push_back(const T& value) {
    ensure_capacity(sz + 1);
    std::construct_at(elems + sz, value);
    ++sz;
  }

  void push_back(T&& value) {
    ensure_capacity(sz + 1);
    std::construct_at(elems + sz,std::move(value));
    ++sz;
  }

  void pop_back() {
    if (sz > 0) {
      std::destroy_at(elems + sz - 1);
      --sz;
    }
  }

  iterator begin() noexcept {return elems;}
  iterator end() noexcept {return elems + sz;}
  const_iterator begin() const noexcept {return elems;}
  const_iterator end() const noexcept {return elems + sz;}

private:
  T* elems = nullptr;
  std::size_t sz = 0;
  std::size_t cap = 0;
  std::allocator<T> alloc{};

  void ensure_capacity(size_t min_capacity) {
    if (min_capacity <= cap) {
      return;
    }
    size_type new_capacity = cap == 0 ? 1 : cap * 2;

    pointer new_elems = alloc.allocate(new_capacity);

    for (size_type i = 0;i < sz;++i) {
      std::construct_at(new_elems + i, std::move(elems[i]));
      std::destroy_at(elems + i);
    }

    if (elems) {
      alloc.deallocate(elems, cap);
    }
    elems = new_elems;
    cap = new_capacity;
  }
};
