/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** get_next_arg_pos.c
*/

#include <string.h>
#include <unistd.h>

int get_next_arg_pos(char **temp, int i)
{
    if (temp[i] == NULL)
        return (i);
    for (; temp[i] != NULL; i++) {
        if (strcmp(temp[i], "&&") == 0 || strcmp(temp[i], "||") == 0 ||
            strcmp(temp[i], "|") == 0 || strcmp(temp[i], ";") == 0 ||
            strcmp(temp[i], "<") == 0 || strcmp(temp[i], ">") == 0 ||
            strcmp(temp[i], ">>") == 0 || strcmp(temp[i], "<<") == 0) {
            return (i);
        }
    }
    return (i - 1);
}
