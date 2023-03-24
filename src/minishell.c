/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** minishell
*/

#include "my.h"
#include <signal.h>

char *clean_str_minishell(char *str, const char *to_clean);
int execute_commands(char **args, term_t *term);
int parsing_error(char **args);
char **edit_args_env(char **args, char **env);

static char *read_stdin(term_t *term)
{
    char *str = NULL;
    size_t size = 0;

    if (getline(&str, &size, stdin) == EOF) {
        (isatty(0) == 1) ? write(1, "exit\n", 5) : 0;
        exit((*term->exit_status == 45) ? 1 : *term->exit_status);
        free(term->str);
        free(term->argv);
    }
    *term->exit_status = 0;
    str[my_strlen(str) - 1] = '\0';
    return (str);
}

static void my_prompt(void)
{
    my_printf("%s", getcwd(NULL, 0));
    my_printf(" \033[1;32m$>\033[0m ");
}

static void sigint_handler(int sig)
{
    (void)sig;
    my_printf("\n");
    my_prompt();
}

int minishell(char **env)
{
    term_t term = { .str = NULL, .argv = NULL,
        .env = env, .exit_status = malloc(sizeof(int)) };

    signal(SIGINT, sigint_handler);
    TAILQ_INIT(&term.pid_list);
    while (1) {
        if (isatty(0) == 1)
            my_prompt();
        term.str = read_stdin(&term);
        if (term.str[0] == '\0')
            continue;
        term.str = clean_str_minishell(term.str, " \t");
        term.argv = my_str_to_word_array(term.str, ' ');
        term.argv = edit_args_env(term.argv, term.env);
        if (term.argv == NULL)
            continue;
        if (parsing_error(term.argv) == 1)
            continue;
        execute_commands(term.argv, &term);
    }
}
