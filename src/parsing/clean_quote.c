/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** clean_quote
*/

#include "my.h"

static const char backslash[4][2] = 
{
    "\\",
    "  ",
    "t\t",
    "n\n"
};

static void remove_char(char *str)
{
    for (int i = 0; str[i]; i++)
        str[i] = str[i + 1];
}

static void check_backslash(char *str, int n)
{
    if (str[0] != '\\')
        return;
    for (int i = 0; i < n; i++)
        if (str[1] == backslash[i][0]) {
            str[0] = backslash[i][1];
            remove_char(str + 1);
            return;
        }
    remove_char(str);
}

static void pass_quote(char *str, int *i, char quote)
{
    remove_char(str + *i);

    for (; str[*i]; *i += 1) {
        check_backslash(str + *i, 4);
        if (str[*i] == quote) {
            remove_char(str + *i);
            break;
        }
    }
}

void clean_quote(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] == '"')
            pass_quote(str, &i, '"');
        if (str[i] == '\'')
            pass_quote(str, &i, '\'');
        check_backslash(str + i, 2);
    }
}
