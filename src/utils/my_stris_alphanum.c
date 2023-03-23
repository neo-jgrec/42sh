/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** my_stris_alphanum
*/

#include "my.h"

bool my_str_isalphanum(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (IS_ALPHANUM(str[i]) == false && str[i] != '_')
            return (false);
    }
    return (true);
}
