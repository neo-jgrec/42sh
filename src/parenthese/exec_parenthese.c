/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** exec_parenthese
*/

#include "my.h"

static char *remove_parenthese(char *input)
{
    char *new_str = NULL;
    size_t to_dup = my_strlen(new_str) - 2;

    new_str = my_strndup(&input[1], to_dup);
    if (new_str == NULL)
        return NULL;
    return new_str;
}

int exec_parenthese(char *input)
{
    char *command = remove_parenthese(input);

    if (command == NULL)
        return 84;
    return 0;
}
