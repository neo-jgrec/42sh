/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** strcat_len
*/

#include "my.h"

char *strcat_len(char *dest, char *str, int len)
{
    int index = 0;
    int len_dest = 0;
    char *buff = NULL;

    for (; dest[len_dest]; len_dest++);
    buff = malloc(sizeof(char) * (len_dest + len + 1));
    for (int i = 0; i < len_dest + len + 1; buff[i] = '\0', i++);
    for (int i = 0; i < len_dest; i++)
        buff[index++] = dest[i];
    for (int i = 0; i < len; i++)
        buff[index++] = str[i];
    free(dest);
    return buff;
}
