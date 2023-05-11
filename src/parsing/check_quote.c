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
    write(2, "Unmatched '", 11);
    write(2, &quote, 1);
    write(2, "'.\n", 3);
    return 0;
}
