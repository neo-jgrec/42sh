/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** joker
*/

#include "my.h"

const char *my_jokers[] = {";", "||", "|", "<<", ">>", ">", "<", "&&",
    "(", ")", NULL};

int is_joker(const char *str, const char **jokers)
{
    for (int k = 0; jokers[k] != NULL; k++) {
        if (strncmp(str, jokers[k], strlen(jokers[k])) == 0)
            return strlen(jokers[k]);
    }
    return 0;
}

char *add_space_before_and_after_jokers(char *str)
{
    char *new_str = malloc(sizeof(char) * strlen(str) * 3 + 1);
    int j = 0;
    int len = 0;

    for (int i = 0; str[i] != '\0'; ) {
        if ((len = is_joker(str + i, my_jokers))) {
            (i > 0 && str[i - 1] != ' ') ? new_str[j++] = ' ' : 0;
            strncpy(new_str + j, str + i, len);
            j += len;
            (str[i + len] != ' ' && str[i + len] != '\0')
                ? new_str[j++] = ' ' : 0;
            i += len;
        } else
            new_str[j++] = str[i++];
    }
    new_str[j] = '\0';
    return new_str;
}
