/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** joker
*/

#include "my.h"

int my_strncmp_tok(char* s1, char* s2, int n);

const char *my_jokers[] = {";", "|", "<<", ">>", ">", "<", NULL};

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

void make_for_statement(char *str, int *i, int *j, char *new_str)
{
    int joker_len = get_joker_len(str, *i, my_jokers);

    for (int k = 0; k < joker_len; k++)
        new_str[(*j)++] = str[(*i) + k];
    *i += joker_len - 1;
}

char *add_space_before_and_after_jokers(char *str)
{
    char *new_str = malloc(sizeof(char) * my_strlen(str) * 3 + 1);
    int j = 0;

    for (int i = 0, in_quote = 0; str[i] != '\0'; i++) {
        in_quote = (IS_QUOTE(str[i]) ? !in_quote : in_quote);
        if (in_quote || !is_joker(str[i], my_jokers))
            new_str[j++] = str[i];
        if (!in_quote && is_joker(str[i], my_jokers)) {
            (i > 0 && !IS_SPACE(str[i - 1])) ? new_str[j++] = ' ' : 0;
            int joker_len = get_joker_len(str, i, my_jokers);
            make_for_statement(str, &i, &j, new_str);
            (str[i + joker_len] != '\0' && !IS_SPACE(str[i + joker_len])) ?
            new_str[j++] = ' ' : 0;
        }
    }
    new_str[j] = '\0';
    return new_str;
}
