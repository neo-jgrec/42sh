/*
** EPITECH PROJECT, 2023
** manage_history
** File description:
** manage_history
*/

#include "my.h"

void manage_history(history_list_t *list, char **command)
{
    history_t *node = NULL;

    if (!list)
        return;
    node = list->head;
    create_history_node(list, command);
    for (; node->next; node = node->next)
        if (command_is_in_history(command, list))
            rm_history_node(node, list);
    if (list->size > 100)
        rm_history_node(list->head, list);
}
