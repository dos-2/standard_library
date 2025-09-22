#include <concepts>
#include <utility>
#include <new>
#include <type_traits>
#include <stdexcept>
#include <memory>

template <typename T>
class optional {
public:
  constexpr optional () noexcept : engaged(false) {}

  constexpr optional(const T& value) : engaged(true) {
    std::construct_at(std::launder(reinterpret_cast<T*>(&storage)), value);
  }

  constexpr optional (T&& value) noexcept(std::is_nothrow_move_constructible_v<T>) : engaged(true) {
    std::construct_at(std::launder(reinterpret_cast<T*>(&storage)), std::move(value));
  }

  constexpr optional(const optional& other) {
    if (other.engaged) {
      std::construct_at(ptr(), *other);
      engaged = true;
    }
  }

  constexpr optional(optional&& other) noexcept(std::is_nothrow_move_constructible_v<T>) {
    if (other.engaged) {
      std::construct_at(ptr(), std::move(*other));
      engaged = true;
    }
  }

  ~optional() { reset();}

  constexpr bool has_value() const noexcept {return engaged;}
  constexpr explicit operator bool() const noexcept {return engaged;}
  constexpr T& operator *() & {return *ptr();}
  constexpr const T& operator *() const& {return *ptr();}
  constexpr T* operator ->() noexcept {return ptr();}
  constexpr const T* operator->() const noexcept {return ptr();}

  void reset() noexcept {
    if (engaged) {
      std::destroy_at(ptr());
      engaged = false;
    }
  }

  template<typename... Args>
  T& emplace(Args&&... args) {
    reset();
    std::construct_at(ptr(), std::forward<Args>(args)...);
    engaged = true;
    return *ptr();
  }

private:
  alignas(T) unsigned char storage[sizeof(T)];
  bool engaged;

  constexpr T* ptr() noexcept {
    return std::launder(reinterpret_cast<T*>(&storage));
  }

  constexpr const T* ptr() const noexcept {
    return std::launder(reinterpret_cast<T*>(&storage));
  }
};
