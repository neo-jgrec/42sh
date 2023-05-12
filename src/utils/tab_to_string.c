/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** tab_to_string
*/

#include "my.h"

char *my_tab_to_string(char **tab, bool with_space)
{
    char *str = malloc(sizeof(char) * BUFFER_SIZE);
    int i = 0;

    if (!tab) return NULL;
    memset(str, 0, BUFFER_SIZE);
    for (; tab[i]; i++) {
        if (with_space && i != 0)
            str = my_strcat(str, " ");
        str = my_strcat(str, tab[i]);
    }
    return str;
}
