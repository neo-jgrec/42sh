/*
** EPITECH PROJECT, 2023
** my_history
** File description:
** my_history
*/

#include <string.h>
#include "my.h"

int my_history(char **args, UNUSED char **env, int *exit_status, void *data)
{
    term_t *term = data;

    if (!args || !term->history)
        return (1);
    if (strcmp(args[0], "history") == 0) {
        (*exit_status) = exec_history_display(args, term->history);
        return ((*exit_status));
    } else {
        return ((*exit_status));
    }
    printf("History error\n");
    *exit_status = 84;
    return (84);
}
