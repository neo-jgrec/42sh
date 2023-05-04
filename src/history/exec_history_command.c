/*
** EPITECH PROJECT, 2023
** exec_history_command
** File description:
** exec_history_command
*/

#include <string.h>
#include "my.h"

static bool handle_error(char **args, history_list_t *list)
{
    if (!args || !list)
        return (true);
    if (strcmp(args[0], "!") == 0){
        printf("!: Command not found.\n");
        return (true);
    }
    if (!is_existant_event(&args[0][1], list)) {
        printf("%s: Event not found.\n", &args[0][1]);
        return (true);
    }
    return (false);
}

int exec_history_command(char **args, history_list_t *list)
{
    if (handle_error(args, list))
        return (1);
    return (0);
}
