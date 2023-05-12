/*
** EPITECH PROJECT, 2023
** convert_args
** File description:
** convert_args
*/

#include "my.h"

static char **get_last_cmd(char **args, history_t *node)
{
    char **cmd = my_dup_array((const char **)node->command);
    size_t a_size = my_count_array_size((const char **)cmd);
    char *to_add = NULL;

    if (strlen(args[0]) == 2)
        return (cmd);
    to_add = malloc(sizeof(char) * strlen(cmd[a_size - 1] +
    strlen(&args[0][2]) + 1));
    if (!to_add)
        return (NULL);
    to_add[0] = '\0';
    to_add = my_strcat(to_add, cmd[a_size - 1]);
    to_add = my_strcat(to_add, &args[0][2]);
    free(cmd[a_size - 1]);
    cmd[a_size - 1] = strdup(to_add);
    free(to_add);
    return (cmd);
}

char **convert_args(char **args, history_list_t *list, bool is_num)
{
    char **new_cmd = NULL;
    history_t *node = list->tail;

    for (; node; node = node->prev){
        if ((is_num && node->pos == atoi(&args[0][1])) || (!is_num &&
        strncmp(&args[0][1], node->command[0], strlen(&args[0][1])) == 0)) {
            new_cmd = my_dup_array((const char **)node->command);
            break;
        }
    }
    if (args && args[0][1] == '!')
        new_cmd = get_last_cmd(args, list->tail);
    if (my_count_array_size((const char **)args) != 1) {
        for (size_t i = 1; args[i]; i++)
            new_cmd = my_add_str_to_array(new_cmd, args[i]);
    }
    return (new_cmd);
}
