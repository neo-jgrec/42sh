/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** clean_quote
*/

#include "my.h"

static const char backslash[13][2] = {
    "\\",
    "  ",
    "\"\"",
    "''",
    "t\t",
    "n\n",
    "``",
    "e\e",
    "f\f",
    "r\r",
    "v\v",
    "a\a",
    "b\b"
};

void remove_char(char *str)
{
    for (int i = 0; str[i]; i++)
        str[i] = str[i + 1];
}

static int check_backslash(char *str, int n, int *i)
{
    if (str[*i] != '\\')
        return 0;
    for (int j = 0; j < n; j++)
        if (str[*i + 1] == backslash[j][0]) {
            str[*i] = backslash[j][1];
            remove_char(str + (*i + 1));
            *i += 1;
            return 1;
        }
    remove_char(str + (*i + 1));
    return 1;
}

static void pass_quote(char *str, int *i, char quote)
{
    remove_char(str + *i);

    for (; str[*i]; *i += 1) {
        check_backslash(str, 13, i);
        if (str[*i] == quote && str[*i - 1] != '\\') {
            remove_char(str + *i);
            break;
        }
    }
}

void clean_quote(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (check_backslash(str, 4, &i)) {
            i--;
            continue;
        }
        if (str[i] == '"' && (i == 0 || str[i - 1] != '\\')){
            pass_quote(str, &i, '"');
        }
        if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
            pass_quote(str, &i, '\'');
    }
}
