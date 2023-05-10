/*
** EPITECH PROJECT, 2023
** store_history
** File description:
** store_history
*/

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "my.h"

static void write_into_file(FILE *stream, history_list_t *history)
{
    history_t *node = history->head;

    for (; node; node = node->next){
        fprintf(stream, "%i %s ", node->pos, node->time);
        for (size_t i = 0; node->command[i]; i++){
            fprintf(stream, "%s ", node->command[i]);
        }
        fprintf(stream, "\n");
    }
}

static void modify_chmod(void)
{
    int fd = open("history.txt", O_RDONLY);

    if (fd == -1) {
        fd = open("history.txt", O_CREAT);
        close(fd);
        chmod("history.txt", 0755);
    } else {
        close(fd);
        chmod("history.txt", 0755);
    }
}

void store_history(history_list_t *history)
{
    FILE *fd = NULL;

    if (!history)
        return;
    if (history->size == 0) {
        free(history);
        return;
    }
    modify_chmod();
    fd = fopen("history.txt", "w+");
    write_into_file(fd, history);
    fclose(fd);
    chmod("history.txt", S_IRUSR);
    destroy_history(history);
}
