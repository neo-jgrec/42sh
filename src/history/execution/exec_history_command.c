/*
** EPITECH PROJECT, 2023
** exec_history_command
** File description:
** exec_history_command
*/

#include <string.h>
#include "my.h"
int execute_commands(char **args, term_t *term, int input, int output);

bool is_existant_event(char *str, history_list_t *list)
{
    history_t *node = list->tail;
    bool check_nb = my_str_isnum(str);

    if (str[0] == '!')
        return (true);
    for (; node; node = node->prev){
        if (check_nb && atoi(str) == node->pos)
            return (true);
        if (!check_nb && node->command && strncmp (node->command[0], str,
        strlen(str)) == 0)
            return (true);
    }
    return (false);
}

static bool handle_error(char **args, history_list_t *list)
{
    if (!args || !list)
        return (true);
    if (strcmp(args[0], "!") == 0){
        dprintf(2, "!: Command not found.\n");
        return (true);
    }
    if (!is_existant_event(&args[0][1], list)) {
        dprintf(2, "%s: Event not found.\n", &args[0][1]);
        return (true);
    }
    return (false);
}

int exec_history_command(char **args, history_list_t *list, term_t *term)
{
    bool is_num = false;
    char **new_cmd = NULL;
    int exit_status = 0;

    if (handle_error(args, list))
        return (1);
    if (args[0][1] != '!') {
        is_num = my_str_isnum(&args[0][1]);
        new_cmd = convert_args(args, list, is_num);
    } else
        new_cmd = my_dup_array((const char **)list->tail->command);
    display_command_array(new_cmd);
    my_destroy_str_array(args);
    command_is_in_history(list->tail->command, list);
    if (list->size > 100)
        rm_history_node(list->head, list);
    exit_status = execute_commands(new_cmd, term, 0, 1);
    return (exit_status);
}
