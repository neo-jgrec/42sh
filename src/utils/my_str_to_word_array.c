/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** my_str_to_word_array
*/

#include "my.h"

static char *fill_line(char const *str, int pos, char const separator)
{
    int tmp = pos;
    int len = 0;
    char *line;

    for (; str[pos] != separator && str[pos] != '\0'; pos++)
        len++;
    line = malloc(sizeof(char) * (len + 1));
    for (int pos = 0; str[tmp] != separator && str[tmp] != '\0'; pos++, tmp++)
        line[pos] = str[tmp];
    line[len] = '\0';
    return line;
}

static int count_word(char const *str, int pos, char const separator)
{
    int letter = 0;

    for (;str[pos] != separator && str[pos] != '\0'; pos++)
        letter++;
    if (letter != 0)
        return 1;
    return 0;
}

static char **fill_tab(char const *str, char const separator, int nbr_word)
{
    int pos_tab = 0;
    char **tab = malloc(sizeof(char *) * (nbr_word + 1));

    if (!tab)
        return NULL;
    for (int pos = 0; str[pos] != '\0' && nbr_word != 0;) {
        for (;str[pos] == separator && str[pos] != '\0'; pos++);
        tab[pos_tab] = fill_line(str, pos, separator);
        pos_tab++;
        for (;str[pos] != separator && str[pos] != '\0'; pos++);
    }
    tab[nbr_word] = NULL;
    return tab;
}

char **my_str_to_word_array(char *str, char c)
{
    int nbr_word = 0;

    if (str == NULL)
        return NULL;
    for (int pos = 0; str[pos] != '\0';) {
        nbr_word += count_word(str, pos, c);
        for (;str[pos] != c && str[pos] != '\0'; pos++);
        for (;str[pos] == c && str[pos] != '\0'; pos++);
    }
    return fill_tab(str, c, nbr_word);
}
