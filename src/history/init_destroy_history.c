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

void rm_history_node(history_t *node, history_list_t *list)
{
    if (!node || !list)
        return;
    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;
    if (node == list->head)
        list->head = node->next;
    if (node == list->tail)
        list->tail = node->prev;
    free(node->time);
    my_destroy_str_array(node->command);
    free(node);
    list->size--;
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
