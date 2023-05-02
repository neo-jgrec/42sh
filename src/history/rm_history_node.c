/*
** EPITECH PROJECT, 2023
** remove_node
** File description:
** remove_node
*/

#include "my.h"

static void destroy_node_content(history_t *node)
{
    free(node->time);
    for (size_t i = 0; node->command[i]; i++)
        free(node->command[i]);
    free(node->command);
    free(node);
}

void rm_history_node(history_t *node, history_list_t *list)
{
    if (node){
        if (node->prev)
            node->prev->next = node->next;
        if (node->next)
            node->next->prev = node->prev;
        if (node == list->head)
            list->head = node->next;
        if (node == list->tail)
            list->tail = node->prev;
        destroy_node_content(node);
    }
}
