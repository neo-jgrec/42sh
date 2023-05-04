/*
** EPITECH PROJECT, 2023
** is_existant_event
** File description:
** is_existant_event
*/

#include <string.h>
#include "my.h"

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
