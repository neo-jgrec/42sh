/*
** EPITECH PROJECT, 2023
** create_history_node
** File description:
** create_history_node
*/

#include <time.h>
#include "my.h"

static char *get_time(void)
{
    time_t mytime = time(NULL);
    char *complete_time = ctime(&mytime);
    char *time = NULL;

    complete_time[my_strlen(complete_time)-1] = '\0';
    time = my_strndup(&complete_time[11], 5);
    return (time);
}

static history_t *init_node(const char **command, history_list_t *list)
{
    history_t *node = NULL;

    if (!list || !command)
        return (NULL);
    node = malloc(sizeof(history_t));
    if (!node)
        return (NULL);
    node->command = my_dup_array(command);
    node->time = get_time();
    if (list->tail)
        node->pos = list->tail->pos + 1;
    else
        node->pos = 1;
    node->next = NULL;
    node->prev = list->tail;
    return (node);
}

void create_history_node(history_list_t *list, char **command)
{
    history_t *node = init_node((const char **)command, list);

    if (!node || !list)
        return;
    if (list->size == 0){
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    list->size++;
}
