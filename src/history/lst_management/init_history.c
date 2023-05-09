/*
** EPITECH PROJECT, 2023
** init_destroy_history
** File description:
** init__destroy_history
*/

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "my.h"

static void add_node_to_history(history_list_t *history, char *pos, char *time,
char **command)
{
    history_t *node = malloc(sizeof(history_t));

    if (!node || !history)
        return;
    node->pos = atoi(pos);
    node->time = my_strdup(time);
    node->command = my_dup_array((const char **)command);
    node->next = NULL;
    node->prev = history->tail;
    if (history->size == 0) {
        history->head = node;
        history->tail = node;
    } else {
        history->tail->next = node;
        history->tail = node;
    }
    history->size++;
}

static void add_file_content_to_list(char **commands, history_list_t *history)
{
    char **temp = NULL;

    if (!commands)
        return;
    for (size_t i = 0; commands[i]; i++) {
        temp = my_str_tok(commands[i], " ");
        if (!temp[0] || !temp[1] || !temp[2])
            continue;
        add_node_to_history(history, temp[0], temp[1], &temp[2]);
        my_destroy_str_array(temp);
    }
}

static void get_old_history(UNUSED history_list_t *history)
{
    int fd = open("history.txt", O_RDONLY);
    struct stat stats;
    char *buffer = NULL;
    char **commands = NULL;

    if (fd == -1 || stat("history.txt", &stats) == -1)
        return;
    buffer = malloc(sizeof(char) * (stats.st_size + 1));
    if (!buffer)
        return;
    read(fd, buffer, stats.st_size);
    buffer[stats.st_size] = '\0';
    if (buffer[0] == '\0') {
        free(buffer);
        return;
    }
    commands = my_str_tok(buffer, "\n");
    add_file_content_to_list(commands, history);
    close(fd);
}

history_list_t *init_history_list(void)
{
    history_list_t *history = malloc(sizeof(history_list_t));

    if (!history)
        return (NULL);
    history->head = NULL;
    history->tail = NULL;
    history->size = 0;
    get_old_history(history);
    return (history);
}
