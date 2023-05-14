/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** print_alias.c
*/

#include "my.h"
#include "list.h"

int print_alias(linked_list_t *alias)
{
    struct linked_list_node *node;
    alias_t *alias_struct;

    if (alias == NULL)
        return (0);
    TAILQ_FOREACH(node, &alias->head, nodes) {
        alias_struct = node->data;
        if (alias_struct->status == 1)
            my_printf("%s\t(%s)\n", ((alias_t *)alias_struct)->command[0],
            ((alias_t *)alias_struct)->command[1]);
        else
            my_printf("%s\t%s\n", ((alias_t *)alias_struct)->command[0],
            ((alias_t *)alias_struct)->command[1]);
    }
    return (0);
}