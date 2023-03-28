/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** logic_gates
*/

#include "my.h"
#include <sys/wait.h>

int execute_command(char **args, int input_fd, int output_fd, term_t *term);

void my_and(exec_t *exec, int *i, term_t *term, char **args)
{
    args[*i] = NULL;
    exec->last_pid = execute_command(args + exec->cmd_start,
    exec->input_fd, exec->output_fd, term);
    int status;
    waitpid(exec->last_pid, &status, 0);
    if (exec->input_fd != STDIN_FILENO)
        close(exec->input_fd);
    if (exec->output_fd != STDOUT_FILENO)
        close(exec->output_fd);
    exec->input_fd = STDIN_FILENO;
    exec->output_fd = STDOUT_FILENO;
    exec->cmd_start = *i + 1;
    if ((WIFEXITED(status) && WEXITSTATUS(status) != 0)) {
        for (int j = exec->cmd_start; args[j]; j++)
            args[j] = args[j + 1];
        if (args[*i + 1])
            remove_element_at_index(args, *i + 1);
        *i = exec->cmd_start - 1;
    }
}

void my_or(exec_t *exec, int *i, term_t *term, char **args)
{
    args[*i] = NULL;
    exec->last_pid = execute_command(args + exec->cmd_start,
    exec->input_fd, exec->output_fd, term);
    int status;
    waitpid(exec->last_pid, &status, 0);
    if (exec->input_fd != STDIN_FILENO)
        close(exec->input_fd);
    if (exec->output_fd != STDOUT_FILENO)
        close(exec->output_fd);
    exec->input_fd = STDIN_FILENO;
    exec->output_fd = STDOUT_FILENO;
    exec->cmd_start = *i + 1;
    if ((WIFEXITED(status) && WEXITSTATUS(status) == 0)) {
        for (int j = exec->cmd_start; args[j]; j++)
            args[j] = args[j + 1];
        if (args[*i + 1])
            remove_element_at_index(args, *i + 1);
        *i = exec->cmd_start - 1;
    }
}
