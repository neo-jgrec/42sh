/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** my_unalias.c
*/

#include "my.h"
#include "list.h"
#include <string.h>


int my_unalias(char **args, UNUSED char **env, int *exit_status, void *data)
{
    term_t *term = (term_t *)data;
    struct linked_list_node *node;

    if (args[1] == NULL) {
        my_printf("unalias: Too few arguments.\n");
        *exit_status = 1;
        return *exit_status;
    }
    TAILQ_FOREACH(node, &term->alias->head, nodes) {
        if (strcmp(((char **)node->data)[0], args[1]) == 0) {
            TAILQ_REMOVE(&term->alias->head, node, nodes);
            *exit_status = 0;
            return *exit_status;
        }
    }
    *exit_status = 1;
    return *exit_status;
}
