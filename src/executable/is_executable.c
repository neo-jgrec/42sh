/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** is_executable
*/

#include "my.h"

char *get_command_with_path(char *cmd, char **env)
{
    char *path = my_getenv(env, "PATH");
    char **path_array = my_str_to_word_array(path, ':');
    char *tmp = NULL;

    if (path_array == NULL)
        return (NULL);
    for (int i = 0; path_array[i] != NULL; i++) {
        tmp = my_strcat_inf(3, path_array[i], "/", cmd);
        if (strchr(cmd, '/') != NULL && access(tmp, F_OK) == 0) {
            free(tmp);
            continue;
        }
        if (access(tmp, F_OK) == 0)
            return (tmp);
        free(tmp);
    }
    return (NULL);
}

char *get_command_with_path_local_var(char *cmd, term_t *term)
{
    char **path_array = my_str_to_word_array(*term->var, ' ');
    char *tmp = NULL;

    if (path_array == NULL)
        return (NULL);
    for (int i = 0; path_array[i] != NULL; i++) {
        tmp = my_strcat_inf(3, path_array[i], "/", cmd);
        if (strchr(cmd, '/') != NULL && access(tmp, F_OK) == 0) {
            free(tmp);
            continue;
        }
        if (access(tmp, F_OK) == 0)
            return (tmp);
        free(tmp);
    }
    return (NULL);
}

int is_executable(char ***args, char **env, term_t *term)
{
    term->is_from_path = 0;
    if (*args[0] == NULL) return (0);
    if (access(*args[0], X_OK) == 0) return (1);
    char *cmd_with_path = get_command_with_path(*args[0], env);
    if (cmd_with_path == NULL)
        cmd_with_path = get_command_with_path_local_var(*args[0], term);
    if (cmd_with_path == NULL)
        return (0);
    free(*args[0]);
    *args[0] = cmd_with_path;
    term->is_from_path = 1;
    return (1);
}
