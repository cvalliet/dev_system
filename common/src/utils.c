#include <errno.h>
#include <utils.h>

pid_t my_fork()
{
    pid_t child_pid;

    do {
        child_pid = fork();
    } while ((0 > child_pid) && (EAGAIN == errno));

    if (0 > child_pid)
        return -errno;

    return child_pid;
}
