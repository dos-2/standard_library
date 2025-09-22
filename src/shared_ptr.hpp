#include <concepts>
#include <functional>
#include <utility>
#include <new>
#include <type_traits>
#include <stdexcept>
#include <memory>

template <typename T>
class shared_ptr {
public:
  shared_ptr() noexcept = default;
  explicit shared_ptr(T* p) : ptr(p) {
    if (p) {
      ref_count = new std::size_t(1);
    } else {
      ref_count = nullptr;
    }
  }

  shared_ptr(const shared_ptr& p) noexcept : ptr(p.ptr), ref_count(p.ref_count) {
    if (ref_count) {
      ++(*ref_count);
    }
  }

  shared_ptr(shared_ptr&& p) noexcept : ptr(p.ptr), ref_count(p.ref_count) {
    p.ptr = nullptr; 
    p.ref_count = nullptr;
  }

  ~shared_ptr() {
    release();
  }

  shared_ptr& operator=(const shared_ptr& other) noexcept {
    if (this != &other) {
      release();
      ptr = other.ptr;
      ref_count = other.ref_count;
      if (ref_count) {
        ++(*ref_count);
      }
    }
    return *this;
  }

  shared_ptr& operator=(shared_ptr&& other) noexcept {
    if (this != &other) {
      release();
      ptr = other.ptr;
      ref_count = other.ref_count;
      other.ptr = nullptr;
      other.ref_count = nullptr;
    }
    return *this;
  }

  T& operator*() const {
    if (!ptr) throw std::runtime_error("Dereferencing a null shared_ptr");
    return *ptr;
  }

  T* operator->() const noexcept {
    return ptr;
  }

  std::size_t use_count() const noexcept {
    return ref_count ? *ref_count : 0;
  }

  explicit operator bool() const noexcept {
    return ptr != nullptr;
  }

  T* get() const noexcept {return ptr;}

  void reset() noexcept {
    release();
    ptr = nullptr;
    ref_count = nullptr;
  }

  void reset(T* p) {
    release();
    ptr = p;
    if (p) {
      ref_count = new std::size_t(1);
    } else {
      ref_count = nullptr;
    }
  }

  void swap(shared_ptr& other) noexcept {
    std::swap(ptr, other.ptr);
    std::swap(ref_count, other.ref_count);
  }

private:
  T* ptr = nullptr;
  std::size_t* ref_count = nullptr;

  void release() noexcept {
    if (ref_count) {
      --(*ref_count);
      if (*ref_count == 0) {
        delete ptr;
        delete ref_count;
      }
    }
  }
};
