#pragma once

#include <stddef.h>

typedef enum _arg_type_t
{
    EXECUTABLE,
    NO_ARGS,
    SHORT_OPTION,
    LONG_OPTION,
    OPTION_VALUE,
    END_OPTION,
    ARGUMENT
} arg_type_t;

typedef enum _arg_status_t
{
    ERROR = -1,
    OK = 0,
    STORE_VALUE,
    EMPTY
} arg_status_t;

typedef arg_status_t (*check_arg_t)(int, arg_type_t, const char*, void*);

arg_status_t parse_args(int, char* [], char, check_arg_t, void*);
