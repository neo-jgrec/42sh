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

    if (nb_args > 3) {
        printf("history: Too many arguments.");
        return (true);
    }
    for (size_t i = 1; args[i]; i++) {
        if (!my_str_isnum(args[i])){
            printf("Usage: history [# number of events].\n");
            return (true);
        }
    }
    return (false);
}

int exec_history_display(char **args, UNUSED history_list_t *list)
{
    if (handle_error_args(args) || !list)
        return (1);
    display_history(list);
    return (0);
}
