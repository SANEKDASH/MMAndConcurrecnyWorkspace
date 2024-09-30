include_directories(include)

# Testing
add_gtest(
    NAME free_list_allocator
    SOURCES tests/allocator_test.cpp
)