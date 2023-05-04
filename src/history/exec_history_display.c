/*
** EPITECH PROJECT, 2023
** exec_history_display
** File description:
** exec_history_display
*/

#include "my.h"

static bool my_str_isnum(const char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++)
        if (!IS_NUM(str[i]))
            return (false);
    return (true);
}

static bool handle_error_args(char **args)
{
    size_t nb_args = my_count_array_size((const char **)args);

    if (!args)
        return (true);
    if (nb_args > 3) {
        printf("history: Too many arguments.");
        return (true);
    }
    for (size_t i = 1; args[i]; i++) {
        if (!my_str_isnum(args[i])){
            printf("Usage: history [number of events].\n");
            return (true);
        }
    }
    return (false);
}

static void display_history_part(char *nb_str, history_list_t *list)
{
    history_t *node = list->head;
    int nb = atoi(nb_str);

    for (size_t i = 0; node; node = node->next, i++){
        if (i >= list->size - nb) {
            printf("\t%i\t%s\t", node->pos, node->time);
            display_command_array(node->command);
        }
    }
}

int exec_history_display(char **args, history_list_t *list)
{
    if (handle_error_args(args) || !list)
        return (1);
    if (my_count_array_size((const char**)args) == 1 ||
    atoi(args[1]) >= (int)list->size) {
        display_history(list);
        return (0);
    }
    display_history_part(args[1], list);
    return (0);
}
