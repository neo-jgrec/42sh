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
int parsing_error(char **args);
char *read_stdin(term_t *term);
char **a_mkstw(char *str, char *sep);

char *remove_home(char *str, char **env)
{
    char *home = my_getenv(env, "HOME");

    if (home == NULL)
        return (str);
    if (my_strncmp(str, home, my_strlen(home)) == 0)
        return (my_strcat_inf(2, "~", str + my_strlen(home)));
    return (str);
}

size_t my_prompt(char **env)
{
    size_t size = 0;

    size += my_printf("\033[1;32m%s\033[0m", " ➜ ");
    size += my_printf("\033[1;34m%s\033[0m", remove_home(getcwd(NULL, 0), env));
    size += my_printf("\033[1;32m%s\033[0m", " ");
    return (size);
}

void handle_sigint_program(int sig)
{
    (void)sig;
}

int minishell(char **env)
{
    term_t term = { .str = NULL, .argv = NULL,
        .env = env, .exit_status = &(int){0},
        init_history_list(), .alias = ll_init_linked_list()};

    TAILQ_INIT(&term.pid_list);
    while (1) {
        term.str = read_stdin(&term);
        if (term.str[0] == '\0')
            continue;
        term.str = clean_str_minishell(term.str, " \t");
        term.str = replace_alias(term.str, term.alias);
        term.argv = a_mkstw(term.str, " ");
        if (term.argv == NULL)
            continue;
        manage_history(term.history, term.argv);
        if (parsing_error(term.argv) == 1)
            continue;
        signal(SIGINT, handle_sigint_program);
        execute_commands(term.argv, &term);
    }
}
