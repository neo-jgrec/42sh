/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** exec_parenthese
*/

#include "my.h"

char **a_mkstw(char *str, char *sep);
char **cpy_env(char **env);

static char *remove_parenthese(char *input)
{
    char *new_str = NULL;
    size_t to_dup = my_strlen(new_str) - 2;

    new_str = my_strndup(&input[1], to_dup);
    if (new_str == NULL)
        return NULL;
    return new_str;
}

static int exec_par_input(term_t *n_term)
{
    pid_t pid;
    int state;

    pid = fork();
    if (pid == -1)
        perror_exit("fork");
    if (pid == 0) {
        exc_par_child(n_term);
    } else {
        pid = wait(&state);
    }
    return 0;
}

int exec_parenthese(char *input, char **env)
{
    term_t new_term = { .str = NULL, .argv = NULL,
        .env = cpy_env(env), .exit_status = &(int){0},
        init_history_list()};
    char *command = remove_parenthese(input);

    if (command == NULL)
        return 1;
    command = clean_str(command, " \t");
    new_term.str = command;
    new_term.argv = a_mkstw(command, " ");
    if (new_term.argv == NULL)
        return 1;
    return exec_par_input(&new_term);
}
