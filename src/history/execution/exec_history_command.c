/*
** EPITECH PROJECT, 2023
** exec_history_command
** File description:
** exec_history_command
*/

#include <string.h>
#include "my.h"
int execute_commands(char **args, term_t *term);

bool is_existant_event(char *str, history_list_t *list)
{
    history_t *node = list->tail;
    bool check_nb = my_str_isnum(str);

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
        printf("!: Command not found.\n");
        return (true);
    }
    if (!is_existant_event(&args[0][1], list)) {
        printf("%s: Event not found.\n", &args[0][1]);
        return (true);
    }
    return (false);
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
    if (my_count_array_size((const char **)args) != 1)
        for (size_t i = 1; args[i]; i++)
            new_cmd = my_add_str_to_array(new_cmd, args[i]);
    return (new_cmd);
}

int exec_history_command(char **args, history_list_t *list, term_t *term)
{
    bool is_num = false;
    char **new_cmd = NULL;
    int exit_status = 0;

    if (handle_error(args, list))
        return (1);
    is_num = my_str_isnum(&args[0][1]);
    new_cmd = convert_args(args, list, is_num);
    my_destroy_str_array(args);
    command_is_in_history(list->tail->command, list);
    if (list->size > 100)
        rm_history_node(list->head, list);
    exit_status = execute_commands(new_cmd, term);
    return (exit_status);
}
