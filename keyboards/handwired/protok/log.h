#pragma once

#include "print.h"
#include "debug.h"

enum {
    LOG_DEBUG = 0,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
};

#ifdef __ENABLE_LOG

extern uint8_t log_level;

#define log_init(lv) \
    do { \
        log_level = lv; \
    } while (0)

#define log_info(fmt, ...) \
    do { \
        if (log_level <= LOG_INFO) \
            printf("[I] " fmt, ##__VA_ARGS__); \
    } while (0)

#define log_warn(fmt, ...) \
    do { \
        if (log_level <= LOG_WARN) \
            printf("[R] " fmt, ##__VA_ARGS__); \
    } while (0)

#define log_error(fmt, ...) \
    do { \
        if (log_level <= LOG_ERROR) \
            printf("[E] " fmt, ##__VA_ARGS__); \
    } while (0)

#define log_debug(fmt, ...) \
    do { \
        if (log_level <= LOG_DEBUG) \
            printf("[D] " fmt, ##__VA_ARGS__); \
    } while (0)

#else

#define log_info(fmt, ...)
#define log_warn(fmt, ...)
#define log_error(fmt, ...)
#define log_debug(fmt, ...)

#endif
