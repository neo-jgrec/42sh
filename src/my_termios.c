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

const term_t *term_ptr;
const struct handler_args_s *handler_args_ptr;

size_t my_prompt(char **env);
void disable_raw_mode(struct termios *orig_termios);

void handle_sigint(int sig)
{
    char *str = handler_args_ptr->str;
    size_t *index = handler_args_ptr->index;
    char *c = handler_args_ptr->c;
    int *exit_status = term_ptr->exit_status;

    (void)sig;
    memset(str, 0, BUFFER_SIZE);
    *exit_status = 1;
    *c = 0;
    *index = 0;
    fflush(stdout);
}

void handle_arrowkeys(char *str, size_t *index)
{
    char seq[3];

    if (read(STDIN_FILENO, &seq[0], 1) != 1) return;
    if (read(STDIN_FILENO, &seq[1], 1) != 1) return;
    if (seq[0] == '[' && seq[1] == 'A') return;
    if (seq[0] == '[' && seq[1] == 'B') return;
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

void handle_action(char *str, size_t *index, char c,
struct termios *orig_termios)
{
    if (c == '\003') {
        str[0] = '\0';
        *index = 0;
        printf("\n");
        my_prompt(term_ptr->env);
    }
    if (c == '\177') {
        if (*index > 0) {
            memmove(&str[*index - 1], &str[*index], strlen(str) - *index + 1);
            (*index)--;
            printf("\033[D\033[P%s", &str[*index]);
        }
    }
    if (c == '\004') {
        if (strlen(str)) return;
        disable_raw_mode(orig_termios);
        printf("exit\n");
        exit((*term_ptr->exit_status == 45) ? 1 : *term_ptr->exit_status);
    }
}

void default_action_case(char *str, size_t *index, char c)
{
    if (*index < BUFFER_SIZE - 1) {
        memmove(&str[*index + 1], &str[*index], strlen(str) - *index + 1);
        str[*index] = c;
        (*index)++;
    }
    printf("%s", &str[*index - 1]);
}

void process_keypress(char *str, struct termios *orig_termios, term_t *term)
{
    char c = 0;
    size_t index = 0;
    handler_args_ptr = &(struct handler_args_s){str, orig_termios, &index, &c};
    term_ptr = term;
    struct sigaction sa;
    sa = (struct sigaction){.sa_handler = handle_sigint, .sa_flags = 0};
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    my_prompt(term->env);
    while (true) {
        read(STDIN_FILENO, &c, 1);
        if (!c || c == '\n') break;
        if (c == '\033')
            handle_arrowkeys(str, &index);
        if (c == '\003' || c == '\177' || c == '\004')
            handle_action(str, &index, c, orig_termios);
        if (c != '\033' && c != '\003' && c != '\177' && c != '\004')
            default_action_case(str, &index, c);
        fflush(stdout);
    }
}
