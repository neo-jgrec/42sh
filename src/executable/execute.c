/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** execute
*/

#include "my.h"

void setup_input_output(int *input_fd, int *output_fd)
{
    if (*input_fd != STDIN_FILENO) {
        dup2(*input_fd, STDIN_FILENO);
        close(*input_fd);
    }
    if (*output_fd != STDOUT_FILENO) {
        dup2(*output_fd, STDOUT_FILENO);
        close(*output_fd);
    }
}

void execute_command_execve(char **args, char **env)
{
    if (execve(args[0], args, env) == -1) {
        perror_exit(args[0]);
    }
}

int execute_non_builtin_command(char **args, int *input_fd,
int *output_fd, char **env)
{
    pid_t pid = fork();
    if (pid < 0) {
        perror_exit("fork");
    } else if (pid == 0) {
        setup_input_output(input_fd, output_fd);
        execute_command_execve(args, env);
    }
    return pid;
}
