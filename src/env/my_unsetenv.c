/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** my_unsetenv
*/

#include "my.h"
#include <string.h>

static int my_strncmp_tok(char* s1, char* s2, int n)
{
    char* token1;
    char* token2;

    token1 = strtok(s1, "");
    token2 = strtok(s2, "");
    for (; token1 != NULL && token2 != NULL && n > 0; n--) {
        if (*token1 != *token2)
            return *token1 - *token2;
        token1 = strtok(NULL, "");
        token2 = strtok(NULL, "");
    }
    return 0;
}

int my_unsetenv(char *str, char **env)
{
    int count = 0;
    size_t len = my_strlen(str);

    for (int i = 0; env[i] != NULL; i++) {
        if (my_strncmp_tok(env[i], str, len) != 0 || env[i][len] != '=')
            continue;
        for (int j = i; env[j] != NULL; j++)
            env[j] = env[j + 1];
        count++;
    }
    return count;
}
