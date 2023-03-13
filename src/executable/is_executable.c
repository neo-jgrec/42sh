/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** is_executable
*/

#include "my.h"

static char *get_command_with_path(term_t *term)
{
    char *tmp = malloc(1000);

    if (term->path == NULL)
        return (NULL);
    for (int i = 0; term->path[i] != NULL; i++) {
        tmp = my_strcpy(tmp, term->path[i]);
        tmp = my_strcat_inf(2, tmp, "/", term->argv[0]);
        if (access(tmp, F_OK) == 0) {
            return (tmp);
        }
    }
    char *absolute_path = my_strcat(getcwd(NULL, 0), "/");
    absolute_path = my_strcat(absolute_path, term->argv[0]);
    if (access(absolute_path, F_OK) == 0) {
        return (absolute_path);
    }
    return (NULL);
}

int is_executable(term_t *term)
{
    term->command_with_path = get_command_with_path(term);
    if (term->command_with_path == NULL) {
        my_printf("%s: Command not found.\n", term->argv[0]);
        term->exit_status = 1;
        return (0);
    }
    if (access(term->command_with_path, X_OK) == 0) {
        term->action = EXEC;
        my_printf("EXECUTABLE\n");
        return (1);
    }
    my_printf("%s: Permission denied.\n", term->argv[0]);
    term->exit_status = 1;
    return (0);
}