/*
** EPITECH PROJECT, 2023
** manage_history
** File description:
** manage_history
*/

#include "my.h"

void manage_history(history_list_t *list, char **command)
{
    if (!list)
        return;
    create_history_node(list, command);
    command_is_in_history(command, list);
    if (list->size > 100)
        rm_history_node(list->head, list);
}
