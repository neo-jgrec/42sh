/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** clean_str_minishell
*/

#include "my.h"

char *add_space_before_and_after_jokers(char *str);

static void remplace_char(char *new_str, int *j)
{
    new_str[*j] = ' ';
    *j = *j + 1;
}

char *clean_str_minishell(char *str, const char *to_clean)
{
    char *new_str = malloc(sizeof(char) * (my_strlen(str) + 3));
    int j = 0;
    int in_quote = 0;

    if (new_str == NULL) return (NULL);
    str = add_space_before_and_after_jokers(str);
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] == '"') && (i == 0 || str[i - 1] != '\''))
            in_quote = !in_quote;
        if (in_quote || my_strchr(to_clean, str[i]) == NULL) {
            new_str[j++] = str[i];
            continue;
        }
        if (i > 0 && my_strchr(to_clean, str[i - 1]) == NULL && !in_quote)
            remplace_char(new_str, &j);
    }
    for (; j > 0 && my_strchr(to_clean, new_str[j - 1]) != NULL; j--);
    new_str[j] = '\0';
    return (new_str);
}
