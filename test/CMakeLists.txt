include(FetchContent)

# Download GoogleTest if not already available
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# Make it available
FetchContent_MakeAvailable(googletest)
# Add test executable
add_executable(standard_library_tests test_array.t.cpp test_vector.t.cpp test_optional.t.cpp)

# Link the header-only library
target_link_libraries(standard_library_tests PRIVATE standard_library GTest::gtest_main)

enable_testing()

# Optional: automatically discover tests if using GoogleTest
include(GoogleTest)
gtest_discover_tests(standard_library_tests)

