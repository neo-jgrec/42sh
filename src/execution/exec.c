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
#include <unistd.h>
#include <signal.h>

void heredoc(char **args, int *input_fd, int *i);
char **edit_args_env(char **args, char **env);

int execute_command(char **args, int input_fd, int output_fd, term_t *term)
{
    int is_builtin = is_builtins(args);
    int is_executable_int = (is_builtin == 0)
    ? is_executable(&args, (char **)term->env) : 0;
    my_fd_t fd = {&input_fd, &output_fd};

    if (edit_args_env(args, (char **)term->env) == NULL) {
        *term->exit_status = 1;
        return 0;
    } else if (is_executable_int == 0 && is_builtin == 0) {
        my_printf("%s: Command not found.\n", args[0]);
        *term->exit_status = 1;
        return 0;
    }
    if (is_builtin)
        return execute_builtin_command(args, (char **)term->env,
        term, fd);
    if (is_executable_int)
        return execute_non_builtin_command(args, fd, term->env, term);
    return 0;
}

void my_parsing(exec_t *exec, char **args, term_t *term)
{
    for (int i = 0; args[i] != NULL; ++i) {
        if (!my_strcmp(args[i], "<")) {
            my_left_redirection(args, &exec->input_fd, &i);
        }
        if (!my_strcmp(args[i], "<<")) {
            heredoc(args, &exec->input_fd, &i);
            continue;
        }
        if (!my_strcmp(args[i], ">")
        || !(exec->append = my_strcmp(args[i], ">>"))) {
            my_right_redirection(args, &exec->output_fd, &i, exec->append);
            continue;
        }
        if (!my_strcmp(args[i], "|")) {
            my_pipe(exec, i, term, args);
            continue;
        }
        if (!my_strcmp(args[i], ";"))
            my_semicolon(exec, &i, term, args);
    }
}

int execute_commands(char **args, term_t *term)
{
    exec_t exec = {0, 1, 0, 0, 0};

    my_parsing(&exec, args, term);
    exec.last_pid = execute_command(args + exec.cmd_start,
    exec.input_fd, exec.output_fd, term);
    pid_list_t *pid_list = malloc(sizeof(pid_list_t));
    TAILQ_FOREACH(pid_list, &term->pid_list, entries) {
        waitpid(pid_list->pid, term->exit_status, 0);
        sigsegv_handler(term);
    }
    if (exec.input_fd != STDIN_FILENO)
        close(exec.input_fd);
    if (exec.output_fd != STDOUT_FILENO)
        close(exec.output_fd);
    if (WIFEXITED(*term->exit_status))
        *term->exit_status = WEXITSTATUS(*term->exit_status);
    return 0;
}
