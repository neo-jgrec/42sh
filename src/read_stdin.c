/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** read_stdin
*/

#include "my.h"

char *strcat_len(char *dest, char *str, size_t len);

void check_quote(char *str, int *quote, int *d_quote, int i)
{
    if (*quote == 0 && *d_quote == 0) {
        if (str[i] == '\"')
            *d_quote += 1;
        if (str[i] == '\'')
            *quote += 1;
        return;
    }
    if (*quote == 1) {
        if (str[i] == '\'')
            *quote -= 1;
        return;
    }
    if (*d_quote == 1) {
        if (str[i] == '\"')
            *d_quote -= 1;
        return;
    }
}

void manage_quote(char *str, int *quote, int *d_quote)
{
    for (int i = 0; str[i]; i++)
        check_quote(str, quote, d_quote, i);
}

char *whole_read_stdin(term_t *term, char *buff)
{
    int quote = 0;
    int d_quote = 0;
    size_t size = 0;
    char *str = NULL;
    int i = 0;

    do {
        if (i++ != 0)
            my_printf(">");
        if (getline(&str, &size, stdin) == EOF) {
            (isatty(0) == 1) ? write(1, "exit\n", 5) : 0;
            exit((*term->exit_status == 45) ? 1 : *term->exit_status);
            free(term->str);
            free(term->argv);
        }
        manage_quote(str, &quote, &d_quote);
        buff = strcat_len(buff, str, (int)size);
    } while (quote % 2 == 1 || d_quote % 2 == 1);
    return buff;
}

char *read_stdin(term_t *term)
{
    char *buff = malloc(sizeof(char));

    buff[0] = '\0';
    buff = whole_read_stdin(term, buff);
    *term->exit_status = 0;
    buff[my_strlen(buff) - 1] = '\0';
    return buff;
}
