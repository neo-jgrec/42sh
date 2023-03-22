/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** my_setenv
*/

#include "my.h"
#include <stdbool.h>
#include <string.h>

void add_element_tab_tail(char **tab, char *element)
{
    int i = 0;

    for (; tab[i] != NULL; i++);
    tab[i] = element;
    tab[i + 1] = NULL;
}

int my_setenv(char *name, char *value, char **env)
{
    char *tmp;

    for (int idx = 0; env[idx] != NULL; idx++) {
        if (my_strncmp(env[idx], name, my_strlen(name)) == 0
        && env[idx][my_strlen(name)] == '=') {
            tmp = malloc(sizeof(char) * my_strlen(name) + my_strlen(value) + 2);
            my_strcpy(tmp, name);
            my_strcat(tmp, "=");
            my_strcat(tmp, value);
            env[idx] = tmp;
            return 0;
        }
    }
    tmp = malloc(sizeof(char) * my_strlen(name) + my_strlen(value) + 2);
    my_strcpy(tmp, name);
    my_strcat(tmp, "=");
    my_strcat(tmp, value);
    add_element_tab_tail(env, tmp);
    return 0;
}
