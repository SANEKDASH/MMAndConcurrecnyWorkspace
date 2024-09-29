include_directories(include)

# Testing
add_gtest(
    NAME bump_pointer_allocator
    SOURCES tests/allocator_test.cpp
)