/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** len_of_array_content.c
*/

#include <string.h>

int len_of_array_content(char **array)
{
    int size = 0;

    for (int i = 0; array[i] != NULL; i++) {
        size += strlen(array[i]);
    }
    return (size);
}
