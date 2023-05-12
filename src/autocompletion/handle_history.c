/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** handle_history
*/

#include "my.h"
extern const term_t *term_ptr;
char *my_tab_to_string(char **tab, bool with_space);

static char *get_history_command_by_index_from_tail(bool to_head,
size_t *history_pos)
{
    history_t *history = term_ptr->history->tail;
    size_t i = 0;

    if (to_head) {
        for (; history && i < *history_pos; i++)
            history = history->prev;
    } else {
        for (; history && i > *history_pos; i--)
            history = history->next;
    }
    if (!history) return NULL;
    return my_tab_to_string(history->command, true);
}

void handle_history(char *str, size_t *index, size_t *history_pos, bool to_head)
{
    char *history_command = get_history_command_by_index_from_tail(to_head,
        history_pos);

    if (history_command) {
        printf("\033[%zuD\033[K", strlen(str));
        memset(str, 0, BUFFER_SIZE);
        strcpy(str, history_command);
        *index = strlen(str);
        printf("%s", str);
        fflush(stdout);
        if (to_head)
            *history_pos = *history_pos == term_ptr->history->size - 1 ?
                term_ptr->history->size - 1 : *history_pos + 1;
        else
            *history_pos = *history_pos == 0 ? 0 : *history_pos - 1;
    }
}
