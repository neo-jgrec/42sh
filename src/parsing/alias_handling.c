/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** alias_handling.c
*/

#include "my.h"
#include "list.h"
#include <string.h>

static int len_of_array_content(char **array)
{
    int size = 0;

    for (int i = 0; array[i] != NULL; i++) {
        size += strlen(array[i]);
    }
    return (size);
}

static char *get_new_str(char **temp)
{
    int len_of_array = len_of_array_content(temp) + 1;
    char *new_str = malloc(sizeof(char) * (len_of_array));

    if (new_str == NULL)
        return (NULL);
    new_str[0] = '\0';
    for (int i = 0; temp[i] != NULL; i++) {
        new_str = strcat(new_str, temp[i]);
        if (temp[i + 1] != NULL)
            new_str = strcat(new_str, " ");
    }
    return (new_str);
}

char *replace_alias(char *str, linked_list_t *alias)
{
    struct linked_list_node *node;
    char **temp = my_str_to_word_array(str, ' ');

    if (temp == NULL || alias == NULL)
        return (str);
    for (int i = 0; temp[i] != NULL; i++) {
        if (strcmp(temp[i], "alias") == 0) {
            i++;
            continue;
        }
        TAILQ_FOREACH(node, &alias->head, nodes) {
            if (strcmp(temp[i], ((char **)node->data)[0]) == 0) {
                temp[i] = strdup(((char **)node->data)[1]);
            }
        }
    }
    str = get_new_str(temp);
    my_destroy_str_array(temp);
    return (str);
}
