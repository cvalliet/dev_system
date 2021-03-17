#include "common.h"

int fork_example(int argc, char* argv[])
{
    pid_t child_pid;

    do {
        child_pid = fork();
    } while ((0 > child_pid) && (EAGAIN == errno));

    if (0 > child_pid) {
        log_error("fork() fail (%d)\n", errno);
        return EXIT_FAILURE;        
    }

    if (!child_pid) {
        // child processing
        log_info("Child: PID=%ld, PPID=%ld\n", (long)getpid(), (long)getppid());
        return EXIT_SUCCESS;
    }

    // parent processing
    log_info("Parent: PID=%ld, PPID=%ld\n", (long)getpid(), (long)getppid());
    wait(NULL);
    return EXIT_SUCCESS;
}

void usage()
{
    fprintf(stderr,
        "Usage: process [EXAMPLE NAME]\n"
        "\n"
        "Launch code example."
        "\n"
        "List of available examples\n"
        "   fork_example : Process creation using fork()\n"
        "\n"); 
}

typedef int (*example_process_t)(int, char* []);
typedef struct _context
{
    const char*       executable_;
    example_process_t example_;    
} context;

arg_status_t option_process(int index, arg_type_t type, const char* arg, void* private)
{
    context* ctx = (context*)private;

    if (EXECUTABLE == type) {
        ctx->executable_ = arg;
        return OK;
    }

    if (NO_ARGS == type) {
        usage();
        return OK;
    }

    if (SHORT_OPTION == type) {
        if ('h' == arg[0]) {
            usage();
            return OK;
        }
    } else
    if (LONG_OPTION == type) {
        if (!strcmp("help", arg)) {
            usage();
            return OK;
        }
    } else
    if (ARGUMENT == type) {
        if (!strcmp("fork_example", arg)) {
            ctx->example_ = fork_example;
            return OK;
        }
    }

    log_error("invalid argument : %s\n", arg);
    return ERROR;
}

int main(int argc, char* argv[])
{
    context ctx = { NULL, NULL };

    arg_status_t status = parse_args(argc, argv, '-', option_process, &ctx);
    if (ERROR == status)
        return EXIT_FAILURE;

    if (EMPTY == status)
        return EXIT_SUCCESS;

    if (ctx.example_)
        return (*ctx.example_)(argc, argv);

    return EXIT_SUCCESS;
}
