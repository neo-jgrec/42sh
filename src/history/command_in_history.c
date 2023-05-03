/*
** EPITECH PROJECT, 2023
** command_in_history
** File description:
** command_in_history
*/

#include <stdbool.h>
#include "my.h"

static int array_compare(const char **arr1, const char **arr2)
{
    size_t size_arr1 = my_count_array_size(arr1);
    size_t size_arr2 = my_count_array_size(arr2);

    if (size_arr1 != size_arr2)
        return (-1);
    for (size_t i = 0; i < size_arr1; i++)
        if (my_strcmp(arr1[i], arr2[i]) != 0)
            return (-1);
    return (0);
}

void command_is_in_history(char **command, history_list_t *list)
{
    history_t *node = NULL;
    if (!list)
        return;
    node = list->head;
    for (; node->next; node = node->next) {
        if (array_compare((const char **)command,
        (const char **)node->command) == 0) {
            rm_history_node(node, list);
            break;
        }
    }
}
