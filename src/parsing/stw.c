/*
** EPITECH PROJECT, 2022
** str
** File description:
** str
*/

#include "my.h"

void clean_quote(char *str);

void skip_quote_2(char *str, int *i, int *j, char quote);
void skip_quote(char *str, int *i, char quote);

void a_freestw(char **stw)
{
    for (int i = 0; stw[i] != NULL; i++)
        free(stw[i]);
    free(stw);
}

static int in_list(char c, char b, char *sep)
{
    if (b == '\\')
        return 0;
    for (int i = 0; sep[i] != 0; i++)
        if (sep[i] == c)
            return 1;
    return 0;
}

static int count_words(char *str, char *sep)
{
    int nb = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == '"' || str[i] == '\'')
            skip_quote(str, &i, str[i]);
        if (!in_list(str[i], str[i - 1], sep) &&
            (in_list(str[i + 1], str[i], sep) || str[i + 1] == '\0'))
            nb++;
    }
    return nb;
}

static int add_word(char *str, char **stw, int word, char *sep)
{
    int i = 0;
    int len = 0;

    for (;in_list(str[i], str[i - 1], sep) && str[i] != '\0'; i++);
    for (int j = i; !in_list(str[j], str[j - 1], sep) &&
        str[j] != '\0'; j++, len++)
        if (str[j] == '"' || str[j] == '\'')
            skip_quote_2(str, &j, &len, str[j]);
    stw[word] = malloc(sizeof(char) * (len + 1));
    for (int j = 0; j < len + 1; j++)
        stw[word][j] = '\0';
    for (int j = 0; j < len; j++)
        stw[word][j] = str[j + i];
    return i + len;
}

char **a_mkstw(char *str, char *sep)
{
    int nb = count_words(str, sep);
    char **stw = malloc(sizeof(char *) * (nb + 1));
    int index = 0;

    for (int i = 0; i < nb + 1; i++)
        stw[i] = NULL;
    for (int word = 0; word < nb; word++)
        index += add_word(str + index, stw, word, sep);
    for (int i = 0; i < nb; i++)
        clean_quote(stw[i]);
    return stw;
}
