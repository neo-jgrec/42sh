/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** check_quote
*/

#include "my.h"

int check_quote(char *str)
{
    char quote = 0;

    for (int i = 0; str[i]; i++) {
        if (quote != 0 && quote == str[i]) {
            quote = 0;
            continue;
        }
        if (quote == 0 && (str[i] == '"' || str[i] == '\''))
            quote = str[i];
    }
    if (quote == 0)
        return 1;
    dprintf(2, "Unmatched '%c'.\n", quote);
    return 0;
}
