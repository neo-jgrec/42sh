/*
** EPITECH PROJECT, 2023
** manage_history
** File description:
** manage_history
*/

#include <string.h>
#include "my.h"

static char **transform_command(char **command, history_list_t *list)
{
    char **new_cmd = NULL;

    if (!is_existant_event(&command[0][1], list))
        return (new_cmd);
    new_cmd = convert_args(command, list, my_str_isnum(&command[0][1]));
    return (new_cmd);
}

void manage_history(history_list_t *list, char **command)
{
    char **new_cmd = NULL;
    if (!list || !command[0])
        return;
    if (strncmp(command[0], "!", 1) == 0)
        new_cmd = transform_command(command, list);
    else
        new_cmd = my_dup_array((const char **)command);
    create_history_node(list, new_cmd);
    if (strncmp(command[0], "!", 1) != 0) {
        command_is_in_history(new_cmd, list);
        if (list->size > 100)
            rm_history_node(list->head, list);
    }
    my_destroy_str_array(new_cmd);
}
