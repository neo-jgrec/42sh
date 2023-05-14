/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** check_str
*/

#include "my.h"

char *handle_backstick(char *str, term_t *term);
int check_quote(char *str);
char **a_mkstw(char *str, char *sep);

char **check_str(char *str, UNUSED term_t *term)
{
    if (!check_quote(str))
        return NULL;
    for (int i = 0; str[i]; i++)
        if (str[i] == '\t')
            str[i] = ' ';
    return a_mkstw(str, " \t");
}
