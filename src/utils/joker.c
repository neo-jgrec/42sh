/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** joker
*/

#include "my.h"

const char *my_jokers[] = {";", "|", "<<", ">>", ">", "<", NULL};

int is_joker(char c, const char **jokers)
{
    for (int k = 0; jokers[k] != NULL; k++) {
        if (c == jokers[k][0])
            return 1;
    }
    return 0;
}

char *add_space_before_and_after_jokers(char *str)
{
    char *new_str = malloc(sizeof(char) * my_strlen(str) * 3 + 1);
    int j = 0;

    for (int i = 0, in_quote = 0; str[i] != '\0'; i++) {
        in_quote = (IS_QUOTE(str[i]) ? !in_quote : in_quote);
        if (in_quote || !is_joker(str[i], my_jokers))
            new_str[j++] = str[i];
        else {
            (i > 0 && !is_joker(str[i - 1], my_jokers)
            ? new_str[j++] = ' ' : 0);
            new_str[j++] = str[i];
            (str[i + 1] != '\0' && !is_joker(str[i + 1], my_jokers) ?
            new_str[j++] = ' ' : 0);
        }
    }
    new_str[j] = '\0';
    return new_str;
}
