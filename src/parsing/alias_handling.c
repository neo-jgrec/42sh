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

static int get_next_arg(char **temp, int i)
{
    for (; temp[i] != NULL; i++) {
        if (strcmp(temp[i], "&&") == 0 || strcmp(temp[i], "||") == 0 ||
            strcmp(temp[i], "|") == 0 || strcmp(temp[i], ";") == 0 ||
            strcmp(temp[i], "<") == 0 || strcmp(temp[i], ">") == 0 ||
            strcmp(temp[i], ">>") == 0 || strcmp(temp[i], "<<") == 0) {
            return (i);
        }
    }
    return (i - 1);
}

static char *get_alias_value(char **temp, int i, linked_list_t *alias)
{
    linked_list_node_t *node;

    TAILQ_FOREACH(node, &alias->head, nodes) {
        if (strcmp(((char **)node->data)[0], temp[i]) == 0) {
            temp[i] = strdup(((char **)node->data)[1]);
        }
    }
    return (temp[i]);
}

static int check_alias_loop(char **temp, int i, linked_list_t *alias)
{
    linked_list_node_t *node;
    char *temp_str = NULL;
    char *alias_value = NULL;

    TAILQ_FOREACH(node, &alias->head, nodes) {
        if (strcmp(((char **)node->data)[0], temp[i]) == 0) {
            temp_str = strdup(((char **)node->data)[1]);
            alias_value = strdup(((char **)node->data)[0]);
        }
    }
    TAILQ_FOREACH(node, &alias->head, nodes) {
        if (strcmp(((char **)node->data)[0], temp_str) == 0) {
            if (strcmp(((char **)node->data)[1], alias_value) == 0) {
                printf("Alias loop.\n");
                return 1;
            }
        }
    }
    return 0;
}

char *replace_alias(char *str, linked_list_t *alias)
{
    char **temp = my_str_to_word_array(str, ' ');

    if (temp == NULL || alias == NULL )
        return (str);
    for (int i = 0; temp[i] != NULL; i++) {
        if (strcmp(temp[i], "alias") == 0 || strcmp(temp[i], "unalias") == 0) {
            i = get_next_arg(temp, i);
            continue;
        }
        if (check_alias_loop(temp, i, alias) == 1) {
            temp[i] = NULL;
            continue;
        }
        temp[i] = get_alias_value(temp, i, alias);
    }
    str = get_new_str(temp);
    str[strlen(str)] = '\0';
    my_destroy_str_array(temp);
    return (str);
}
