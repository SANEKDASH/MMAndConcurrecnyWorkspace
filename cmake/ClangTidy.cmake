add_custom_target(clang-tidy-check
  COMMAND ${PROJECT_ROOT}/scripts/codestyle/clang_tidy_check.py --full ${PROJECT_ROOT} ${PROJECT_BINARY_ROOT}
  USES_TERMINAL
)
