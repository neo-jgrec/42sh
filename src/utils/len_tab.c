/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** len_tab
*/

#include "my.h"

int len_tab(char **tab)
{
    int i = 0;

    if (tab == NULL)
        return (0);
    for (; tab[i] != NULL; i++);
    return (i);
}
