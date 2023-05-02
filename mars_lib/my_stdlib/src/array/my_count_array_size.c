/*
** EPITECH PROJECT, 2023
** ml_count_array_size
** File description:
** ml_count_array_size
*/

#include <sys/types.h>

size_t my_count_array_size(const char **array)
{
    size_t counter = 0;

    if (!array)
        return (counter);
    for (; array[counter]; counter++);
    return (counter);
}
