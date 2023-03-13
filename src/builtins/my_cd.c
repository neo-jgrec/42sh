/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** my_cd
*/

#include "my.h"
#include <string.h>

void my_cd(term_t *term)
{
    char *tmp = NULL;

    if (len_tab(term->argv) > 2) {
        my_printf("cd: Too many arguments.\n");
        return;
    }
    if (term->argv[1] == NULL) {
        tmp = my_getenv(term->env, "HOME");
        if (tmp != NULL)
            chdir(tmp);
        else
            my_printf("cd: No home directory.\n");
    } else if (my_strcmp(term->argv[1], "-") == 0)
        chdir(term->old_cwd);
    else
        chdir(term->argv[1]);
    if (errno != 0) {
        my_printf("%s: %s.\n", term->argv[1], strerror(errno));
        errno = 0;
    }
    term->old_cwd = term->cwd;
    term->cwd = getcwd(NULL, 0);
}
