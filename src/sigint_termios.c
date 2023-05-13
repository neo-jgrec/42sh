/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** sigint_termios
*/

#include "my.h"
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

extern const term_t *term_ptr;
extern const struct handler_args_s *handler_args_ptr;

void handle_sigint(int sig)
{
    char *str = handler_args_ptr->str;
    size_t *index = handler_args_ptr->index;
    char *c = handler_args_ptr->c;
    int *exit_status = term_ptr->exit_status;

    (void)sig;
    memset(str, 0, BUFFER_SIZE);
    *exit_status = 1;
    *c = 0;
    *index = 0;
    fflush(stdout);
    write(STDOUT_FILENO, "^C", 2);
}
