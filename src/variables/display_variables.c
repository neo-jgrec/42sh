/*
** EPITECH PROJECT, 2023
** display_variables
** File description:
** display_variables
*/

#include "my.h"

void display_variables(char **var, history_list_t *history)
{
    printf("_");
    if (history->tail && history->tail->prev) {
        printf("\t");
        display_command_array(history->tail->prev->command);
    }
    printf("\n");
    for (size_t i = 0; var && var[i]; i++)
        printf("%s\n", var[i]);
}
