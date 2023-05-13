/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** is_sentence.c
*/

int is_sentence(char const *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++) {
        if (str[i] == ' ')
            return 1;
    }
    return 0;
}
