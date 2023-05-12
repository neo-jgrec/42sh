/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** my_termios
*/

#include "my.h"
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

const term_t *term_ptr;
const struct handler_args_s *handler_args_ptr;
const struct termios *orig_termios_ptr;

void disable_raw_mode(struct termios *orig_termios);
void autocomplete(char *str, size_t *index);
void handle_history(char *str, size_t *index,
    size_t *history_pos, bool to_head);
void handle_sigint(int sig);

void handle_arrowkeys(char *str, size_t *index, size_t *history_pos)
{
    char seq[3];

    if (read(STDIN_FILENO, &seq[0], 1) != 1) return;
    if (read(STDIN_FILENO, &seq[1], 1) != 1) return;
    if (seq[0] == '[' && seq[1] == 'A')
        handle_history(str, index, history_pos, true);
    if (seq[0] == '[' && seq[1] == 'B')
        handle_history(str, index, history_pos, false);
    if (seq[0] == '[' && seq[1] == 'C') {
        if (*index < strlen(str)) {
            write(STDOUT_FILENO, "\033[C", 3);
            (*index)++;
        }
    }
    if (seq[0] == '[' && seq[1] == 'D') {
        if (*index > 0) {
            write(STDOUT_FILENO, "\033[D", 3);
            (*index)--;
        }
    }
}

void handle_action(char *str, size_t *index, char c, size_t *history_pos)
{
    if (c == '\177' && *index > 0) {
        (*index)--;
        memmove(&str[*index], &str[*index + 1], strlen(str) - *index + 1);
        printf("\033[D\033[K%s \033[%zuD", &str[*index],
            strlen(str) - *index + 1);
        fflush(stdout);
    }
    if (c == '\004' && strlen(str) == 0) {
        disable_raw_mode((struct termios *)orig_termios_ptr);
        printf("exit\n");
        exit((*term_ptr->exit_status == 45) ? 1 : *term_ptr->exit_status);
    } else if (c == '\004' && *index < strlen(str) && strlen(str) > 0) {
        memmove(&str[*index], &str[*index + 1], strlen(str) - *index + 1);
        printf("\033[K%s \033[%zuD", &str[*index],
            strlen(str) - *index + 1);
        fflush(stdout);
    }
    if (c == '\t') autocomplete(str, index);
    if (c == '\033') handle_arrowkeys(str, index, history_pos);
}

void default_action_case(char *str, size_t *index, char c)
{
    if (*index < BUFFER_SIZE - 1) {
        memmove(&str[*index + 1], &str[*index], strlen(str) - *index + 1);
        str[*index] = c;
        (*index)++;
        printf("\033[1@%s \033[%zuD", &str[*index - 1],
            strlen(str) - *index + 1);
        fflush(stdout);
    }
}

void process_keypress(char *str, struct termios *orig_termios, term_t *term)
{
    char c = 0;
    size_t index = 0;
    struct sigaction sa = {.sa_handler = handle_sigint, .sa_flags = 0};
    size_t *history_pos = &(size_t){0};

    handler_args_ptr = &(struct handler_args_s){str, orig_termios, &index, &c};
    orig_termios_ptr = orig_termios;
    term_ptr = term;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    while (true) {
        read(STDIN_FILENO, &c, 1);
        if (!c || c == '\n') break;
        if (c == '\177' || c == '\004' || c == '\033' || c == '\t')
            handle_action(str, &index, c, history_pos);
        else
            default_action_case(str, &index, c);
        fflush(stdout);
    }
}
