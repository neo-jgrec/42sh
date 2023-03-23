/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** remove_at_index
*/

#include "my.h"

void remove_element_at_index(char **args, int index)
{
    for (int i = index; args[i] != NULL; ++i)
        args[i] = args[i + 1];
}
