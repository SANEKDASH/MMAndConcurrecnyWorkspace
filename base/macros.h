#ifndef BASE_MACROS_H
#define BASE_MACROS_H

#include <cassert>

// Inline (disabled for DEBUG)
#ifndef NDEBUG
#define ALWAYS_INLINE                                 // NOLINT(cppcoreguidelines-macro-usage)
#else                                                 // NDEBUG
#define ALWAYS_INLINE __attribute__((always_inline))  // NOLINT(cppcoreguidelines-macro-usage)
#endif                                                // !NDEBUG

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define NO_INLINE __attribute__((noinline))

#ifdef __clang__
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define NO_OPTIMIZE [[clang::optnone]]
#else
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define NO_OPTIMIZE __attribute__((optimize("O0")))
#endif

#ifdef __clang__
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define FIELD_UNUSED __attribute__((__unused__))
#else
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define FIELD_UNUSED
#endif

#ifndef PANDA_TARGET_WINDOWS
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define PANDA_PUBLIC_API __attribute__((visibility("default")))
#else
#define PANDA_PUBLIC_API __declspec(dllexport)
#endif

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define MEMBER_OFFSET(T, F) offsetof(T, F)

#if defined(__cplusplus)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define NO_COPY_CTOR(TypeName) TypeName(const TypeName &) = delete;

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define NO_COPY_OPERATOR(TypeName) void operator=(const TypeName &) = delete

// Disabling copy ctor and copy assignment operator.
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define NO_COPY_SEMANTIC(TypeName) \
    NO_COPY_CTOR(TypeName)         \
    NO_COPY_OPERATOR(TypeName)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define NO_MOVE_CTOR(TypeName)                   \
    /* NOLINTNEXTLINE(misc-macro-parentheses) */ \
    TypeName(TypeName &&) = delete;

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define NO_MOVE_OPERATOR(TypeName)               \
    /* NOLINTNEXTLINE(misc-macro-parentheses) */ \
    TypeName &operator=(TypeName &&) = delete

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define NO_MOVE_SEMANTIC(TypeName) \
    NO_MOVE_CTOR(TypeName)         \
    NO_MOVE_OPERATOR(TypeName)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define DEFAULT_MOVE_CTOR(TypeName)              \
    /* NOLINTNEXTLINE(misc-macro-parentheses) */ \
    TypeName(TypeName &&) = default;

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define DEFAULT_MOVE_OPERATOR(TypeName)          \
    /* NOLINTNEXTLINE(misc-macro-parentheses) */ \
    TypeName &operator=(TypeName &&) = default

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define DEFAULT_MOVE_SEMANTIC(TypeName) \
    DEFAULT_MOVE_CTOR(TypeName)         \
    DEFAULT_MOVE_OPERATOR(TypeName)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define DEFAULT_COPY_CTOR(TypeName) TypeName(const TypeName &) = default;

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define DEFAULT_COPY_OPERATOR(TypeName)          \
    /* NOLINTNEXTLINE(misc-macro-parentheses) */ \
    TypeName &operator=(const TypeName &) = default

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define DEFAULT_COPY_SEMANTIC(TypeName) \
    DEFAULT_COPY_CTOR(TypeName)         \
    DEFAULT_COPY_OPERATOR(TypeName)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define DEFAULT_NOEXCEPT_MOVE_CTOR(TypeName)     \
    /* NOLINTNEXTLINE(misc-macro-parentheses) */ \
    TypeName(TypeName &&) noexcept = default;

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define DEFAULT_NOEXCEPT_MOVE_OPERATOR(TypeName) \
    /* NOLINTNEXTLINE(misc-macro-parentheses) */ \
    TypeName &operator=(TypeName &&) noexcept = default

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define DEFAULT_NOEXCEPT_MOVE_SEMANTIC(TypeName) \
    DEFAULT_NOEXCEPT_MOVE_CTOR(TypeName)         \
    DEFAULT_NOEXCEPT_MOVE_OPERATOR(TypeName)

#endif  // defined(__cplusplus)

#define LIKELY(exp) (__builtin_expect((exp) != 0, true))     // NOLINT(cppcoreguidelines-macro-usage)
#define UNLIKELY(exp) (__builtin_expect((exp) != 0, false))  // NOLINT(cppcoreguidelines-macro-usage)

#endif  // BASE_MACROS_H
