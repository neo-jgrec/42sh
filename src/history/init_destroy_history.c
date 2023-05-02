/*
** EPITECH PROJECT, 2023
** init_destroy_history
** File description:
** init__destroy_history
*/

#include "my.h"

history_list_t *init_history_list(void)
{
    history_list_t *history = malloc(sizeof(history_list_t));

    if (!history)
        return (NULL);
    history->head = NULL;
    history->tail = NULL;
    history->size = 0;
    return (history);
}

void destroy_history(history_list_t *list)
{
    history_t *node = NULL;

    if (!list)
        return;
    node = list->tail;
    for (; node->prev; node = node->prev)
        rm_history_node(node, list);
    rm_history_node(node, list);
    free(list); 
}
