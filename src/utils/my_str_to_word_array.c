/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** my_str_to_word_array
*/

#include "my.h"

#include <stdlib.h>
#include <stdbool.h>

static char *fill_line(char const *str, int *pos, char const separator)
{
    int len = 0;
    bool in_quotes = false;

    for (int tmp = *pos ; (str[tmp] != separator && str[tmp] != '\0')
    || in_quotes; tmp++, len++) {
        if (str[tmp] == '"' || str[tmp] == '\'') {
            in_quotes = !in_quotes;
            continue;
        }
    }
    char *line = my_calloc(sizeof(char), len + 1);
    for (int i = 0; (str[*pos] != separator && str[*pos] != '\0')
    || in_quotes; (*pos)++) {
        if (str[*pos] == '"' || str[*pos] == '\'') {
            in_quotes = !in_quotes;
            continue;
        }
        line[i++] = str[*pos];
    }
    return line;
}

static int count_word(char const *str, int *pos, char const separator)
{
    int letter = 0;
    bool in_quotes = false;

    for (; (str[*pos] != separator && str[*pos] != '\0')
    || in_quotes; (*pos)++) {
        if (str[*pos] == '"' || str[*pos] == '\'') {
            in_quotes = !in_quotes;
            continue;
        }
        letter++;
    }
    if (letter != 0)
        return 1;
    return 0;
}

static char **fill_tab(char const *str, char const separator, int nbr_word)
{
    int pos_tab = 0;
    char **tab = malloc(sizeof(char *) * (nbr_word + 1));
    int pos = 0;

    if (!tab)
        return NULL;
    while (str[pos] != '\0' && nbr_word != 0) {
        for (;str[pos] == separator && str[pos] != '\0'; pos++);
        tab[pos_tab] = fill_line(str, &pos, separator);
        pos_tab++;
    }
    tab[nbr_word] = NULL;
    return tab;
}

char **my_str_to_word_array(char *str, char c)
{
    int nbr_word = 0;
    int pos = 0;

    if (str == NULL)
        return NULL;
    while (str[pos] != '\0') {
        nbr_word += count_word(str, &pos, c);
        for (;str[pos] != c && str[pos] != '\0'; pos++);
        for (;str[pos] == c && str[pos] != '\0'; pos++);
    }
    return fill_tab(str, c, nbr_word);
}
