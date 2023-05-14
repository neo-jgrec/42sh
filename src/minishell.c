/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** minishell
*/

#include <time.h>
#include <string.h>
#include "my.h"
#include <signal.h>

char *clean_str_minishell(char *str, const char *to_clean);
char *replace_alias(char *str, linked_list_t *alias);
int execute_commands(char **args, term_t *term);
int parsing_error(char **args, term_t *term);
char *read_stdin(term_t *term);
char **check_str(char *str, term_t *term);
char **a_mkstw(char *str, char *sep, int check_quote);
char **edit_args_env(char **args, char **env);
bool does_var_exist(char *name, char **var);
int check_quote(char *str);

char *remove_home(char *str, char **env)
{
    char *home = my_getenv(env, "HOME");

    if (home == NULL)
        return (str);
    if (my_strncmp(str, home, my_strlen(home)) == 0)
        return (my_strcat_inf(2, "~", str + my_strlen(home)));
    return (str);
}

size_t my_prompt(char **env, term_t *term)
{
    size_t size = 0;

    if (*term->exit_status == 0)
        size += my_printf("\033[1;32m%s\033[0m", " ➜ ");
    else
        size += my_printf("\033[1;31m%s\033[0m", " ➜ ");
    size += my_printf("\033[1;34m%s\033[0m", remove_home(getcwd(NULL, 0), env));
    size += my_printf("\033[1;32m%s\033[0m", " ");
    return (size);
}

void handle_sigint_program(int sig)
{
    (void)sig;
}

void set_special_vars(term_t *term)
{
    size_t size = confstr(_CS_PATH, NULL, 0);
    char *path = my_getenv(term->env, "PATH");

    if (!path && !does_var_exist("path", term->var)) {
        path = malloc(sizeof(char) * size);
        confstr(_CS_PATH, path, size);
        for (size_t i = 0; path[i]; i++)
            path[i] = (path[i] == ':') ? ' ' : path[i];
        my_set("path", path, &term->var);
    }
    if (path) {
        path = strdup(path);
        for (size_t i = 0; path[i]; i++)
            path[i] = (path[i] == ':') ? ' ' : path[i];
        my_set("path", path, &term->var);
    }
    if (my_getenv(term->env, "HOME"))
        my_set("home", my_getenv(term->env, "HOME"), &term->var);
    my_set("?", my_itoa(*term->exit_status), &term->var);
}

int minishell(char **env)
{
    term_t term = { .str = NULL, .argv = NULL, .env = env, .exit_status =
    &(int){0}, init_history_list(), .alias = ll_init_linked_list(), .ac = 0};

    TAILQ_INIT(&term.pid_list);
    while (1) {
        set_special_vars(&term);
        term.str = read_stdin(&term);
        if (term.str[0] == '\0') continue;
        term.str = clean_str_minishell(term.str, " \t");
        term.ac = len_tab(a_mkstw(term.str, " ", 0));
        if (!check_quote(term.str) ||
            !(term.str = replace_alias(term.str, term.alias)) ||
            !(term.argv = a_mkstw(term.str, " \t", 1)))
            continue;
        manage_history(term.history, term.argv);
        if (parsing_error(term.argv, &term) || check_parenthesis(&term))
            continue;
        if (edit_args_env(term.argv, term.env) == NULL) continue;
        signal(SIGINT, handle_sigint_program);
        execute_commands(term.argv, &term);
    }
}
