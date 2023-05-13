/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** handle_backstick
*/

#include "my.h"

void skip_quote(char *str, int *i, char quote);
void remove_char(char *str);
char *fork_call(char *str, char *buff, term_t *term);

static char *put_backstick(char *str, char *backstick)
{
    char *buff = (char *)calloc((my_strlen(str) +
        my_strlen(backstick) + 2),sizeof(char));

    int i = 0;
    int str_index = 0;
    for (; str[str_index] != '`'; i++, str_index++)
        buff[i] = str[i];
    for (int j = 0; backstick[j]; j++, i++)
        buff[i] = backstick[j];
    str_index++;
    for (; str[str_index]; i++, str_index++)
        buff[i] = str[str_index];
    return buff;
}

static void clean_backstick(char *str)
{
    while (str[0]) {
        if (str[0] == '`') {
            remove_char(str);
            return;
        }
        remove_char(str);
    }
}

static char *backstick(char *str, term_t *term)
{
    int index = 0;
    char *duppl = my_strdup(str);
    char *buff = malloc(sizeof(char));

    buff[0] = '\0';
    for (int i = 0; duppl[i]; i++)
        if (duppl[i] == '`')
            duppl[i] = '\0';
    buff = fork_call(duppl, buff, term);
    for (; buff[index]; index++) {
        if (buff[index] == '\n')
            buff[index] = ' ';
    }
    buff[index - 1] = '\0';
    return buff;
}

char *handle_backstick(char *str, term_t *term)
{
    char *buff = NULL;

    for (int i = 0; str[i]; i++) {
        if (str[i] == '\'' || str[i] == '"')
            skip_quote(str, &i, str[i]);
        if (str[i] == '`') {
            buff = backstick(str + i + 1, term);
            clean_backstick(str + i + 1);
            str = put_backstick(str, buff);
            printf("%d '%s'\n", strlen(str)  ,str);
        }
    }
    return str;
}
