#pragma once

#include <stdlib.h>

#define _log(file, prefix, fmt, ...) \
    fprintf(file, "%s: (%s) " fmt, prefix, __func__, __VA_ARGS__)
#define _log_source(file, prefix, fmt, ...) \
    fprintf(file, "%s: (%s, %d, %s) " fmt, prefix, __FILE__, __LINE__, __func__, __VA_ARGS__)

#define log_error(fmt, ...) _log_source(stderr, "ERR", fmt, __VA_ARGS__)
#define log_info(fmt, ...) _log(stderr, "INF", fmt, __VA_ARGS__)
#define log_warning(fmt, ...) _log(stderr, "WRN", fmt, __VA_ARGS__)
