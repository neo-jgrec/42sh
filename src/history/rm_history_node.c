/*
** EPITECH PROJECT, 2023
** remove_node
** File description:
** remove_node
*/

#include "my.h"

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
