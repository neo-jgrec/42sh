/*
** EPITECH PROJECT, 2023
** display_history
** File description:
** display_history
*/

#include <stdio.h>
#include "my.h"

static void display_command_array(char **command)
{
    size_t parser = 0;

    if (!command) {
        printf("\n");
        return;
    }
    for (; command[parser + 1]; parser++)
        printf("%s ", command[parser]);
    printf("%s\n", command[parser]);
}

void display_history(history_list_t *list)
{
    history_t *node = NULL;

    if (!list)
        return;
    node = list->head;
    for (; node; node = node->next) {
        printf("\t%i\t%s\t", node->pos, node->time);
        display_command_array(node->command);
    }
}
