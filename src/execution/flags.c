/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** flags
*/

#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

int execute_command(char **args, int input_fd, int output_fd, term_t *term);
void perror_exit(const char *s);

void my_left_redirection(char **args, int *input_fd, int *i)
{
    if (args[*i + 1] == NULL) {
        dprintf(2, "Missing name for redirect.\n");
        args[*i] = NULL;
        return;
    }
    *input_fd = open(args[*i + 1], O_RDONLY);
    if (*input_fd < 0)
        perror_exit(args[*i + 1]);
    args[*i] = NULL;
    ++(*i);
}

void my_right_redirection(char **args, int *output_fd, int *i, int append)
{
    if (args[*i + 1] == NULL) {
        dprintf(2, "Missing name for redirect.\n");
        args[*i] = NULL;
        return;
    }
    *output_fd = open(args[*i + 1], append ? O_WRONLY | O_CREAT | O_TRUNC
    : O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (*output_fd < 0)
        perror_exit(args[*i + 1]);
    args[*i] = NULL;
    ++(*i);
}

int my_pipe(exec_t *exec, int *i, term_t *term, char **args)
{
    int pipes[2];

    if (pipe(pipes) == -1)
        perror_exit("pipe");
    args[*i] = NULL;
    exec->last_pid = execute_command(args + exec->cmd_start,
    exec->input_fd, pipes[1], term);
    close(pipes[1]);
    if (exec->input_fd != STDIN_FILENO)
        close(exec->input_fd);
    exec->input_fd = pipes[0];
    exec->cmd_start = *i + 1;
    return 0;
}

void my_semicolon(exec_t *exec, int *i, term_t *term, char **args)
{
    while (args[*i + 1] != NULL && my_strcmp(args[*i + 1], ";") == 0)
        remove_element_at_index(args, *i + 1);
    if (args[*i + 1] == NULL) {
        remove_element_at_index(args, *i);
        return;
    }
    args[*i] = NULL;
    exec->last_pid = execute_command(args + exec->cmd_start,
    exec->input_fd, exec->output_fd, term);
    waitpid(exec->last_pid, NULL, 0);
    if (exec->input_fd != STDIN_FILENO)
        close(exec->input_fd);
    if (exec->output_fd != STDOUT_FILENO)
        close(exec->output_fd);
    exec->input_fd = 0;
    exec->output_fd = 1;
    exec->cmd_start = *i + 1;
}
