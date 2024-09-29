include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)

FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

enable_testing()

# Use this target to build all gtests you added
add_custom_target(
  build_all_gtests
)

# Use this target to build and run all gtests you added
add_custom_target(
  run_all_gtests
)

function(add_gtest)
  set(one_value_args NAME)
  set(multi_value_args SOURCES LIBS)
  cmake_parse_arguments(TEST "" "${one_value_args}" "${multi_value_args}" ${ARGN})
  
  message("-- Added test: ${TEST_NAME}")

  add_executable(${TEST_NAME} ${TEST_SOURCES})
  target_link_libraries(${TEST_NAME} PRIVATE GTest::GTest ${TEST_LIBS})

  add_custom_target(
    ${TEST_NAME}_run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}
    DEPENDS ${TEST_NAME}
  )

  add_dependencies(
    build_all_gtests
    ${TEST_NAME}
  )

  add_dependencies(
    run_all_gtests
    ${TEST_NAME}_run
  )

endfunction()

