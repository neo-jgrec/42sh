/*
** EPITECH PROJECT, 2023
** ml_dup_array
** File description:
** ml_dup_array
*/

#include <stdlib.h>
#include "array.h"
#include "my_stdlib.h"

char **my_dup_array(const char **array)
{
    size_t size = my_count_array_size(array);
    char **dup_array = my_create_str_array(size);
    size_t parser = 0;

    if (!dup_array)
        return (NULL);
    for (; array[parser]; parser++)
        dup_array[parser] = my_strdup(array[parser]);
    dup_array[parser] = NULL;
    return (dup_array);
}
