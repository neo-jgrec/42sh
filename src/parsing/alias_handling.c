/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** alias_handling.c
*/

#include "my.h"
#include "list.h"
#include <string.h>

int len_of_array_content(char **array);
int get_next_arg_pos(char **temp, int i);
char **a_mkstw(char *str, char *sep, int check_quote);

static char *get_new_str(char **temp)
{
    int len_of_array = len_of_array_content(temp) + len_tab(temp) - 1;
    char *new_str = calloc(len_of_array, sizeof(char));

    if (new_str == NULL)
        return (NULL);
    new_str[0] = '\0';
    for (int i = 0; temp[i] != NULL; i++) {
        new_str = my_strcat_inf(2, new_str, temp[i]);
        if (temp[i + 1] != NULL)
            new_str = my_strcat_inf(2, new_str, " ");
    }
    return (new_str);
}

static char *get_alias_value(char **temp, int i, linked_list_t *alias)
{
    linked_list_node_t *node;
    alias_t *alias_struct;

    TAILQ_FOREACH(node, &alias->head, nodes) {
        alias_struct = node->data;
        if (strcmp(((alias_t *)alias_struct)->command[0], temp[i]) == 0) {
            temp[i] = strdup(((alias_t *)alias_struct)->command[1]);
        }
    }
    return (temp[i]);
}

static int check_if_loop(char *alias_value, char *temp_str,
linked_list_t *alias)
{
    linked_list_node_t *node;
    alias_t *alias_struct;

    TAILQ_FOREACH(node, &alias->head, nodes) {
        alias_struct = node->data;
        if (strcmp(((alias_t *)alias_struct)->command[0], temp_str) == 0 &&
            strcmp(((alias_t *)alias_struct)->command[1], alias_value) == 0) {
            printf("Alias loop.\n");
            return 1;
        }
    }
    return 0;
}

static int check_alias_loop(char **temp, int i, linked_list_t *alias)
{
    linked_list_node_t *node;
    alias_t *alias_struct;
    char *temp_str = NULL;
    char *alias_value = NULL;

    TAILQ_FOREACH(node, &alias->head, nodes) {
        alias_struct = node->data;
        if (strcmp(((alias_t *)alias_struct)->command[0], temp[i]) == 0) {
            temp_str = strdup(((alias_t *)alias_struct)->command[1]);
            alias_value = strdup(((alias_t *)alias_struct)->command[0]);
        }
    }
    if (temp_str == NULL || alias_value == NULL)
        return 0;
    return (check_if_loop(alias_value, temp_str, alias));
}

char *replace_alias(char *str, linked_list_t *alias)
{
    char **temp = a_mkstw(str, " ", 0);

    if (temp == NULL || alias == NULL || temp[0] == NULL)
        return (str);
    for (int i = 0; temp[i] != NULL; i++) {
        if (strcmp(temp[i], "alias") == 0 || strcmp(temp[i], "unalias") == 0) {
            i = get_next_arg_pos(temp, i);
            continue;
        }
        if (check_alias_loop(temp, i, alias) == 1) {
            str = NULL;
            return (str);
        }
        temp[i] = get_alias_value(temp, i, alias);
    }
    str = get_new_str(temp);
    str[strlen(str)] = '\0';
    my_destroy_str_array(temp);
    return (str);
}
