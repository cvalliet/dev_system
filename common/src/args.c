#include <args.h>

arg_status_t parse_args(int argc, char* argv[], char opt_prefix,
    check_arg_t callback, void* private)
{
    arg_status_t   ret = ERROR;
    int          count = 0, option = 1;
    char**        argp = argv + 1;

    if (!argc || !callback)
        return ERROR;

    ret = callback(count, EXECUTABLE, *argp, private);
    if (OK != ret)
        return ret;

    if (1 == argc)
        return callback(1, NO_ARGS, NULL, private);

    for (--argc; *argp && argc; ++argp, --argc) {
        char*       arg = *argp;
        arg_type_t type = ARGUMENT;

        if (opt_prefix == *arg) {
            if (!option || (STORE_VALUE == ret))
                return ERROR;

            type = SHORT_OPTION;
            ++arg;

            if (opt_prefix == *arg) {
                type = LONG_OPTION;
                ++arg;

                if ('\0' == *arg) {
                    type = END_OPTION;
                    option = 0;
                }
            }
        } else if (option) {
            if (STORE_VALUE == ret)
                type = OPTION_VALUE;
            else
                option = 0;
        }

        ret = callback(count++, type, arg, private);
        if ((OK != ret) || (STORE_VALUE != ret))
            break;
    }

    return ret;
}
