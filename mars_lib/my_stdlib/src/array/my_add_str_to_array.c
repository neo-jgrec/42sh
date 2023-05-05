/*
** EPITECH PROJECT, 2023
** ml_add_str_to_array
** File description:
** ml_add_str_to_array
*/

#include "array.h"
#include "my_stdlib.h"
#include <stdlib.h>

char **my_add_str_to_array(char **array, const char *str)
{
    size_t size = my_count_array_size((const char **)array);
    char **n_array = my_create_str_array(size + 1);

    if (!n_array)
        return (NULL);
    if (array){
        n_array = my_copy_array(n_array, (const char **)array);
        my_destroy_str_array(array);
    }
    n_array[size] = my_strdup(str);
    n_array[size + 1] = NULL;
    return (n_array);
}
