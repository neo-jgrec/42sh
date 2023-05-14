/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** my_which
*/

#include "my.h"

char *get_command_with_path(char *cmd, char **env);

int my_which(char **args, char **env, int *exit_status,
UNUSED void *data)
{
    char *cmd_with_path = get_command_with_path(args[1], env);

    if (args[1] == NULL) {
        dprintf(2, "where: Too few arguments.\n");
        return (1);
    }
    if (cmd_with_path == NULL) {
        *exit_status = 1;
        dprintf(2, "%s: Command not found.\n", args[1]);
        return (1);
    }
    printf("%s\n", cmd_with_path);
    return (0);
}

int my_where(char **args, char **env, UNUSED int *exit_status,
UNUSED void *data)
{
    char *path = my_getenv(env, "PATH");
    char **path_array = my_str_to_word_array(path, ':');
    char *tmp = NULL;

    if (path_array == NULL)
        return (1);
    if (args[1] == NULL) {
        dprintf(2, "where: Too few arguments.\n");
        return (1);
    }
    for (int i = 0; path_array[i] != NULL; i++) {
        tmp = my_strcat_inf(3, path_array[i], "/", args[1]);
        if (access(tmp, F_OK) == 0)
            printf("%s\n", tmp);
        free(tmp);
    }
    return (0);
}
