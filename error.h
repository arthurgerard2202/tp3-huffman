#ifndef ERROR_H_
#define ERROR_H_

#define ATTENTION "\xe2\x9d\x97"
#define HINT "\xe2\x9c\xa8"
#define OK "\xE2\x9C\x85"
#define KO "\xE2\x9D\x8C"

// In X mode, all messages more severe than X are printed.
// clang-format off
enum debug_level {OFF,        CRITICAL, ERROR,     WARNING, INFO,    DEBUG, TRACE};
enum msg_level   {CRITICAL_L, ERROR_L,  WARNING_L, INFO_L,  DEBUG_L, TRACE_L};
// clang-format on

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL INFO
#endif

// __VA_OPTS__ requires C2x. Clang issues spurious warning.

#define PRINT_ERROR(symbol, name, function, file, line, msg, ...) \
  do {                                                            \
    fprintf(stderr,                                               \
            "\n" symbol                                           \
            " ["                                                  \
            name                                                  \
            "]"                                                   \
            " - Function %s (%s:%d) -\n  "                        \
            msg "\n",                                             \
            function, file, line                                  \
            __VA_OPT__( , ) __VA_ARGS__);                         \
  } while (0)

#define FATAL(msg, ...)                                                                             \
  do {                                                                                              \
    PRINT_ERROR(ATTENTION, "FATAL", __func__, __FILE__, __LINE__, msg __VA_OPT__( , ) __VA_ARGS__); \
    exit(EXIT_FAILURE);                                                                             \
  } while (0)

#define PRINT_DEBUG(symbol, name, level, msg, ...)                                            \
  do {                                                                                        \
    if ((int)DEBUG_LEVEL > (int)level)                                                        \
    PRINT_ERROR(symbol, name, __func__, __FILE__, __LINE__, msg __VA_OPT__( , ) __VA_ARGS__); \
  } while (0)

#define TRACE(msg, ...) PRINT_DEBUG(OK, "TRACE", TRACE_L, msg, __VA_ARGS__)

#define DEBUG(msg, ...)  PRINT_DEBUG(HINT, "DEBUG", DEBUG_L, msg, __VA_ARGS__)

#define INFO(msg, ...)  PRINT_DEBUG(HINT, "INFO", INFO_L, msg, __VA_ARGS__)

#define WARNING(msg, ...) PRINT_DEBUG(ATTENTION, "WARNING", WARNING_L, msg, __VA_ARGS__)

#define ERROR(msg, ...) PRINT_DEBUG(ATTENTION, "ERROR", ERROR_L, msg, __VA_ARGS__)

#define CRITICAL(msg, ...) PRINT_DEBUG(KO, "CRITICAL", CRITICAL_L, msg, __VA_ARGS__)

#endif // ERROR_H_
