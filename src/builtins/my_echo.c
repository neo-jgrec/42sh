/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** my_echo
*/

#include "my.h"

static char *get_string_echo(char **argv, int i)
{
    char *str = my_calloc(my_strlen(argv[i]) + 1, sizeof(char));

    for (; argv[i] != NULL; i++) {
        str = my_strcat(str, argv[i]);
        if (argv[i + 1] != NULL)
            str = my_strcat(str, " ");
    }
    return str;
}

char *my_echo(char **argv, UNUSED char **env, UNUSED int *exit_status,
UNUSED void *data)
{
    int n = 0;
    char *str = my_calloc(my_strlen(argv[1]) + 1, sizeof(char));

    if (argv[1] == NULL) {
        my_printf("\n");
        return NULL;
    }
    if (argv[1][0] == '-' && argv[1][1] == 'n') {
        n = 1;
        str = get_string_echo(argv, 2);
    } else
        str = get_string_echo(argv, 1);
    if (n == 0)
        my_printf("%s\n", str);
    else
        my_printf("%s", str);
    return NULL;
}
