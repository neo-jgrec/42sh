/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** minishell
*/

#include "my.h"

char *clean_str_minishell(char *str, const char *to_clean);

static char *read_stdin(term_t *term)
{
    char *str = NULL;
    size_t size = 0;

    if (getline(&str, &size, stdin) == EOF) {
        (isatty(0) == 1) ? write(1, "exit\n", 5) : 0;
        exit(term->exit_status);
    }
    str[my_strlen(str) - 1] = '\0';
    term->exit_status = 0;
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
        .cwd = getcwd(NULL, 0),
        .old_cwd = NULL,
        .action = NONE,
        .exit_status = 0,
        .env = env,
        .path = NULL,
        .command_with_path = NULL
    };

    while (1) {
        term.path = my_str_to_word_array(my_getenv(term.env, "PATH"), ':');
        if (isatty(0) == 1)
            my_prompt();
        term.str = read_stdin(&term);
        if (term.str[0] == '\0')
            continue;
        term.str = clean_str_minishell(term.str, " \t");
        printf("str = |%s|\n", term.str);
        term.argv = my_str_to_word_array(term.str, ' ');
        for (int i = 0; term.argv[i] != NULL; i++)
            my_printf("argv[%d] = |%s|\n", i, term.argv[i]);
        if (term.argv == NULL)
            continue;
        is_builtins(&term);
        // is_executable(&term);
    }
}
