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

static void get_old_history(UNUSED history_list_t *history)
{
    int fd = open("save_file/history.txt", O_RDONLY);
    struct stat stats;
    char *buffer = NULL;
    char **commands = NULL;

    if (fd == -1 || stat("save_file/history.txt", &stats) == -1)
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
