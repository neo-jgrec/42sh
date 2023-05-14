/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** error_handling
*/

#include <unistd.h>
#include "my.h"
#include <sys/wait.h>
#include <string.h>

void perror_exit(const char *s)
{
    if (errno == 8) {
        dprintf(2, "%s: Exec format error. Wrong Architecture.\n", s);
    } else
        dprintf(2, "%s: %s.\n", s, strerror(errno));
    errno = 0;
}

int get_signal(int process_status)
{
    return WIFSIGNALED(process_status)
    ? WTERMSIG(process_status) == 11 ? 139 :
    WTERMSIG(process_status) == 8 ? 136 :
    WTERMSIG(process_status) == 6 ? 134 :
    WTERMSIG(process_status) == 4 ? 132 :
    WTERMSIG(process_status) == 7 ? 135 :
    WTERMSIG(process_status) == 5 ? 133 :
    WTERMSIG(process_status) == 3 ? 131 :
    WTERMSIG(process_status) == 2 ? 130 :
    WTERMSIG(process_status) == 1 ? 129 :
    0
    : 0;
}

void sigsegv_handler(term_t *term)
{
    int sig;

    if (*term->exit_status == 1) return;
    sig = get_signal(*term->exit_status);
    (sig == 139) ? write(2, "Segmentation fault", 18) : 0;
    (sig == 136) ? write(2, "Floating exception", 18) : 0;
    (sig == 134) ? write(2, "Abort", 5) : 0;
    (sig == 132) ? write(2, "Illegal instruction", 19) : 0;
    (sig == 135) ? write(2, "Bus error", 9) : 0;
    (sig == 133) ? write(2, "Trace/breakpoint trap", 21) : 0;
    (sig == 132) ? write(2, "Illegal instruction", 19) : 0;
    (sig == 131) ? write(2, "Quit", 4) : 0;
    (sig == 130) ? write(2, "Interrupt", 9) : 0;
    (sig == 129) ? write(2, "Hangup", 6) : 0;
    if (WCOREDUMP(*term->exit_status)) {
        write(2, " (core dumped)", 14);
        sig = 139;
    }
    if (sig != 0) write(2, "\n", 1);
    if (sig != 0) *term->exit_status = sig;
}
