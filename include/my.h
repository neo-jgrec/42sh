/*
** EPITECH PROJECT, 2023
** project-maker
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_

    #include "mars.h"
    #include <stdio.h>
    #include <unistd.h>
    #include <errno.h>
    #include <stdlib.h>

    typedef struct {
        char *str;
        char **argv;
        char **env;
        int *exit_status;
    } term_t;

    typedef struct commands_s {
        char *name;
        void (*func)(void *args, char **env, int *exit_status);
    } commands_t;

    typedef struct {
        int input_fd;
        int output_fd;
        int cmd_start;
        int append;
        pid_t last_pid;
    } exec_t;

    char *my_getenv(char **env, const char *name);
    int my_setenv(char *name, char *value, char **env);
    int my_unsetenv(char *str, char **env);

    void my_cd(char **args, char **env, int *exit_status);
    int my_unsetenv_builtin(char **args, char **env, int *exit_status);
    int my_setenv_builtin(char **args, char **env, int *exit_status);
    int my_env(char **args, char **env, int *exit_status);
    void my_exit(char **args, char **env, int *exit_status);

    static const struct commands_s commands[] = {
        {"cd", (void *) my_cd},
        {"setenv", (void *) my_setenv_builtin},
        {"unsetenv", (void *) my_unsetenv_builtin},
        {"env", (void *) my_env},
        {"exit", (void *) my_exit},
        {NULL, NULL}
    };

    char **my_str_to_word_array(char *str, const char to_clean);
    int len_tab(char **tab);

    void sigsegv_handler(int sig);
    void perror_exit(const char *s);

    int is_executable(char ***args, char **env);
    int is_builtins(char **args);
    int execute_builtin_command(char **args, char **env,
    int *exit_status);
    int execute_non_builtin_command(char **args, int *input_fd,
    int *output_fd, char **env);

#endif /* !MY_H_ */
