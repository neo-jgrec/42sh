/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** exec setenv | cat -e
*/

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include "my.h"

void my_left_redirection(char **args, int *input_fd, int *i, int append);
void my_right_redirection(char **args, int *output_fd, int *i, int append);
int my_pipe(exec_t *exec, int i, char **env, char **args);
void my_semicolon(exec_t *exec, int i, char **env, char **args);

int execute_command(char **args, int input_fd, int output_fd, char **env)
{
    int is_builtin = is_builtins(args);
    int is_executable_int = (is_builtin == 0) ? is_executable(&args, env) : 0;
    if (is_executable_int == 0 && is_builtin == 0) {
        my_printf("%s: Command not found.\n", args[0]);
        return 0;
    }
        if (is_executable_int == 0 && is_builtin == 0) {
        my_printf("%s: Command not found.\n", args[0]);
        return 0;
    }
    if (is_builtin)
        return execute_builtin_command(args, env, &(int){0});
    if (!is_builtin)
        return execute_non_builtin_command(args, &input_fd, &output_fd, env);
    return 0;
}

void my_parsing(exec_t *exec, char **args, char **env)
{
    for (int i = 0; args[i] != NULL; ++i) {
        if (!my_strcmp(args[i], "<")
        || !(exec->append = my_strcmp(args[i], "<<"))) {
            my_left_redirection(args, &exec->input_fd, &i, exec->append);
            continue;
        }
        if (!my_strcmp(args[i], ">")
        || !(exec->append = my_strcmp(args[i], ">>"))) {
            my_right_redirection(args, &exec->output_fd, &i, exec->append);
            continue;
        }
        if (!my_strcmp(args[i], "|")) {
            my_pipe(exec, i, env, args);
            continue;
        }
        if (!my_strcmp(args[i], ";")) {
            my_semicolon(exec, i, env, args);
            continue;
        }
    }
}

int execute_commands(char **args, char **env)
{
    exec_t exec = {0, 1, 0, 0, 0};

    my_parsing(&exec, args, env);
    exec.last_pid = execute_command(args + exec.cmd_start,
    exec.input_fd, exec.output_fd, env);
    waitpid(exec.last_pid, NULL, 0);
    (exec.input_fd != STDIN_FILENO) ? close(exec.input_fd) : 0;
    (exec.output_fd != STDOUT_FILENO) ? close(exec.output_fd) : 0;
    return 0;
}
