/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** exec_parenthese
*/

#include "my.h"
#include <sys/wait.h>

int execute_commands(char **args, term_t *term);

static void exc_par_child(term_t *n_term)
{
    execute_commands(n_term->argv, n_term);
    exit(0);
}

static int exec_par_input(term_t *n_term)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
        perror_exit("fork");
    if (pid == 0) {
        exc_par_child(n_term);
    } else {
        waitpid(pid, n_term->exit_status, 0);
    }
    return 0;
}

int exec_parenthesis(char **argv, char **env)
{
    term_t new_term = { .str = NULL, .argv = argv,
        .env = env, .exit_status = &(int){0},
        init_history_list()};
    return exec_par_input(&new_term);
}
