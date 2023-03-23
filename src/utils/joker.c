/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** joker
*/

#include "my.h"
int my_strncmp_tok(char* s1, char* s2, int n);

int is_joker(char c, const char **jokers)
{
    for (int k = 0; jokers[k] != NULL; k++) {
        if (c == jokers[k][0])
            return 1;
    }
    return 0;
}

int get_joker_len(const char *str, int index, const char **jokers)
{
    int joker_len = 0;

    for (int k = 0; jokers[k] != NULL; k++) {
        joker_len = my_strlen(jokers[k]);
        if (my_strncmp_tok((char *)(&str[index]),
        (char *)(jokers[k]), joker_len) == 0)
            return joker_len;
    }
    return 0;
}

char *add_space_before_and_after_jokers(char *str)
{
    const char *jokers[] = {";", "|", "<", ">", "<<", ">>", NULL};
    char *new_str = malloc(sizeof(char) * my_strlen(str) * 3 + 1);
    int j = 0;
    int in_quote = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        in_quote = (IS_QUOTE(str[i]) ? !in_quote : in_quote);
        if (in_quote || !is_joker(str[i], jokers))
            new_str[j++] = str[i];
        else {
            ((i > 0 && !is_joker(str[i - 1], jokers) && !in_quote)
            ? (new_str[j++] = ' ') : (0));
            new_str[j++] = str[i];
            i += get_joker_len(str, i, jokers) - 1;
            ((str[i + 1] != '\0' && !is_joker(str[i + 1], jokers)
            && !in_quote) ? (new_str[j++] = ' ') : (0));
        }
    }
    new_str[j] = '\0';
    return new_str;
}
