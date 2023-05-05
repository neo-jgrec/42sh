/*
** EPITECH PROJECT, 2023
** ml_create_array
** File description:
** ml_create_array
*/

#include <stdlib.h>

char **my_create_str_array(size_t size)
{
    char **array = NULL;
    size_t null_seter = 0;

    if (size != 0)
        array = malloc(sizeof(char *) * (size + 1));
    else
        return (NULL);
    if (!array)
        return (NULL);
    for (; null_seter <= size; null_seter++)
        array[null_seter] = NULL;
    return (array);
}
