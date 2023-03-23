/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** execute
*/

#include "my.h"

char *remove_path(char *str)
{
    int i = 0;
    int j = 0;
    char *ret = malloc(sizeof(char) * 100);

    for (; str[i] != '\0'; i++);
    for (; str[i] != '/'; i--);
    for (i++; str[i] != '\0'; i++, j++)
        ret[j] = str[i];
    ret[j] = '\0';
    return (ret);
}

char **change_n_value(char **tab, char *str, int n)
{
    int i = 0;
    int j = 0;
    char **ret = malloc(sizeof(char *) * 100);

    for (; tab[i] != NULL; i++);
    for (int k = 0; k < i; k++) {
        if (k == n) {
            ret[j] = malloc(sizeof(char) * 100);
            my_strcpy(ret[j], str);
            j++;
        } else {
            ret[j] = malloc(sizeof(char) * 100);
            my_strcpy(ret[j], tab[k]);
            j++;
        }
    }
    ret[j] = NULL;
    return (ret);
}

void setup_input_output(int *input_fd, int *output_fd)
{
    if (*input_fd != STDIN_FILENO) {
        dup2(*input_fd, STDIN_FILENO);
        close(*input_fd);
    }
    if (*output_fd != STDOUT_FILENO) {
        dup2(*output_fd, STDOUT_FILENO);
        close(*output_fd);
    }
}

void execute_command_execve(char **args, char **env)
{
    if (execve(args[0],
    change_n_value(args, remove_path(args[0]), 0), env) == -1) {
        perror_exit(args[0]);
    }
}

int execute_non_builtin_command(char **args, int *input_fd,
int *output_fd, char **env)
{
    pid_t pid = fork();

    if (pid < 0) {
        perror_exit("fork");
    } else if (pid == 0) {
        setup_input_output(input_fd, output_fd);
        execute_command_execve(args, env);
    }
    return pid;
}
