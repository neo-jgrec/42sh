/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** skip_quote
*/

void skip_quote(char *str, int *i, char quote)
{
    *i += 1;

    for (; str[*i] != quote && str[*i] != '\0'; *i += 1);
    if (str[*i] == '\0')
        *i -= 1;
}

void skip_quote_2(char *str, int *i, int *j, char quote)
{
    *i += 1;
    *j += 1;

    for (; str[*i] != quote && str[*i] != '\0'; *i += 1, *j += 1);
    if (str[*i] == '\0')
        *i -= 1;
}
