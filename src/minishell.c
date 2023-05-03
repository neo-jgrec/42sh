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
int execute_commands(char **args, term_t *term);
int parsing_error(char **args);

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

static char *remove_home(char *str, char **env)
{
    char *home = my_getenv(env, "HOME");

    if (home == NULL)
        return (str);
    if (my_strncmp(str, home, my_strlen(home)) == 0)
        return (my_strcat_inf(2, "~", str + my_strlen(home)));
    return (str);
}

static void my_prompt(char **env)
{
    my_printf("\033[1;32m%s\033[0m", " ➜ ");
    my_printf("\033[1;34m%s\033[0m", remove_home(getcwd(NULL, 0), env));
    my_printf("\033[1;32m%s\033[0m", " ");
}

static void sigint_handler(int sig)
{
    char *temp_env[] = {"", NULL};

    (void)sig;
    if (isatty(STDIN_FILENO) == 1) {
        my_printf("\n");
        my_prompt(temp_env);
    }
}

int minishell(char **env)
{
    term_t term = { .str = NULL, .argv = NULL,
        .env = env, .exit_status = malloc(sizeof(int)), init_history_list()};

    signal(SIGINT, sigint_handler);
    TAILQ_INIT(&term.pid_list);
    while (1) {
        if (isatty(STDIN_FILENO) == 1)
            my_prompt(env);
        term.str = read_stdin(&term);
        if (term.str[0] == '\0')
            continue;
        term.str = clean_str_minishell(term.str, " \t");
        term.argv = my_str_to_word_array(term.str, ' ');
        manage_history(term.history, term.argv);
        if (term.argv == NULL)
            continue;
        if (parsing_error(term.argv) == 1)
            continue;
        execute_commands(term.argv, &term);
    }
}
