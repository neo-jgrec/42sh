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
void my_parenthesis(UNUSED exec_t *exec, int *i, term_t *term, char **args);

static void error_message(char *str)
{
    if (access(str, F_OK) == 0)
        dprintf(2, "%s: Permission denied.\n", str);
    else
        dprintf(2, "%s: Command not found.\n", str);
}

int execute_command(char **args, int input_fd, int output_fd, term_t *term)
{
    int is_builtin = is_builtins(args);
    int is_executable_int = (is_builtin == 0)
    ? is_executable(&args, (char **)term->env, term) : 0;
    my_fd_t fd = {&input_fd, &output_fd};

    if (args[0] == NULL) return 0;
    if (is_executable_int == 0 && is_builtin == 0) {
        error_message(args[0]);
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
        (!strcmp(args[i], "<")) ? my_left_redirection(args, &exec->input_fd, &i)
        : (!strcmp(args[i], "<<")) ? heredoc(args, &exec->input_fd, &i)
        : (!strcmp(args[i], ">") || !(exec->append = strcmp(args[i], ">>")))
            ? my_right_redirection(args, &exec->output_fd, &i, exec->append)
        : (!strcmp(args[i], "|")) ? my_pipe(exec, &i, term, args)
        : (!strcmp(args[i], "&&")) ? my_and(exec, &i, term, args)
        : (!strcmp(args[i], ";")) ? my_semicolon(exec, &i, term, args)
        : (!strcmp(args[i], "||")) ? my_or(exec, &i, term, args)
        : (!strcmp(args[i], "(")) ? my_parenthesis(exec, &i, term, args)
        : 0;
    }
}

int execute_commands(char **args, term_t *term, int input_fd, int output_fd)
{
    exec_t exec = {input_fd, output_fd, 0, 0, 0};

    my_parsing(&exec, args, term);
    if (args[exec.cmd_start] != NULL)
        exec.last_pid = execute_command(args + exec.cmd_start,
        exec.input_fd, exec.output_fd, term);
    pid_list_t *pid_list = malloc(sizeof(pid_list_t));
    TAILQ_FOREACH(pid_list, &term->pid_list, entries) {
        waitpid(pid_list->pid, term->exit_status, 0);
        if (WIFSIGNALED(*term->exit_status))
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
