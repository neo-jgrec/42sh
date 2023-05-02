/*
** EPITECH PROJECT, 2023
** ml_destroy_array
** File description:
** ml_destroy_array
*/

#include <stdlib.h>

void my_destroy_str_array(char **array)
{
    if (!array)
        return;
    for (size_t parser = 0; array[parser]; parser++)
        free(array[parser]);
    free(array);
}
