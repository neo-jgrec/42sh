/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** minishell
*/

#include "my.h"

char *clean_str_minishell(char *str, const char *to_clean);
int execute_commands(char **args, char **env, term_t *term);

static char *read_stdin(void)
{
    char *str = NULL;
    size_t size = 0;

    if (getline(&str, &size, stdin) == EOF) {
        (isatty(0) == 1) ? write(1, "exit\n", 5) : 0;
        exit(0);
    }
    str[my_strlen(str) - 1] = '\0';
    return (str);
}

static void my_prompt(void)
{
    my_printf("%s", getcwd(NULL, 0));
    my_printf(" \033[1;32m$>\033[0m ");
}

int minishell(char **env)
{
    term_t term = {
        .str = NULL,
        .argv = NULL,
        .env = env,
    };

    while (1) {
        if (isatty(0) == 1)
            my_prompt();
        term.str = read_stdin();
        if (term.str[0] == '\0')
            continue;
        term.str = clean_str_minishell(term.str, " \t");
        term.argv = my_str_to_word_array(term.str, ' ');
        if (term.argv == NULL)
            continue;
        execute_commands(term.argv, term.env, &term);
        free(term.str);
        free(term.argv);
    }
}
