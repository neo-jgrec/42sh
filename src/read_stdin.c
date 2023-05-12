/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** read_stdin
*/

#include "my.h"
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void process_keypress(char *str, struct termios *orig_termios, term_t *term);
char *strcat_len(char *dest, char *str, int len);
size_t my_prompt(char **env);

void enable_raw_mode(struct termios *orig_termios)
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, orig_termios);

    raw = *orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode(struct termios *orig_termios)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios);
}

char *whole_read_stdin(term_t *term, char *buff)
{
    struct termios orig_termios;

    enable_raw_mode(&orig_termios);
    my_prompt(term->env);
    process_keypress(buff, &orig_termios, term);
    disable_raw_mode(&orig_termios);

    return buff;
}

char *whole_read_stdin_no_tty(term_t *term)
{
    char *str = NULL;
    size_t size = 0;

    if (getline(&str, &size, stdin) == EOF) {
        (isatty(0) == 1) ? write(1, "exit\n", 5) : 0;
        exit((*term->exit_status == 45) ? 1 : *term->exit_status);
        free(term->str);
        free(term->argv);
    }
    *term->exit_status = 0;
    str[my_strlen(str) - 1] = '\0';
    return (str);
}

char *read_stdin(term_t *term)
{
    char *buff = calloc(BUFFER_SIZE + 1, sizeof(char));

    buff[0] = '\0';
    if (isatty(0)) {
        buff = whole_read_stdin(term, buff);
        *term->exit_status = 0;
        printf("\n");
        return buff;
    }
    buff = whole_read_stdin_no_tty(term);
    *term->exit_status = 0;
    buff[my_strlen(buff)] = '\0';
    return buff;
}
