/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** exec
*/

#include "my.h"
void setup_input_output(int *input_fd, int *output_fd);

int is_changing_input_output(int *input_fd, int *output_fd)
{
    if (*input_fd != STDIN_FILENO || *output_fd != STDOUT_FILENO)
        return 1;
    return 0;
}

void execute_builtin(char **args, char **env, term_t *term)
{
    for (int i = 0; commands[i].name != NULL; i++) {
        if (my_strcmp(args[0], commands[i].name) == 0) {
            commands[i].func(args, env, term->exit_status);
        }
    }
}

int execute_builtin_command(char **args, char **env,
term_t *term, my_fd_t fd)
{
    pid_t pid;
    pid_list_t *pid_list;

    if (is_changing_input_output(fd.input_fd, fd.output_fd)) {
        pid = fork();
        if (pid == 0) {
            setup_input_output(fd.input_fd, fd.output_fd);
            execute_builtin(args, env, term);
            exit(0);
        } else {
            pid_list = malloc(sizeof(pid_list_t));
            pid_list->pid = pid;
            TAILQ_INSERT_TAIL(&term->pid_list, pid_list, entries);
        }
        return pid;
    } else {
        execute_builtin(args, env, term);
    }
    return 0;
}
