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

    typedef struct {
        char *prog_name;
        int nb_args;
        pid_t PID;
        pid_t child_PID;
        int status;
    } my_process_t;

    typedef enum action_e {
        NONE,
        BUILTINS,
        EXEC
    } action_t;

    typedef struct {
        char *str;
        char **argv;
        char *cwd;
        char *old_cwd;
        action_t action;
        char **env;
        char **path;
        char *command_with_path;
        int exit_status;
    } term_t;

    typedef struct commands_s {
        char *name;
        void (*func)(term_t *term);
    } commands_t;

    char *my_getenv(char **env, char *name);
    int my_setenv(char *name, char *value, char **env);
    int my_unsetenv(char *str, char **env);

    void my_cd(term_t *term);
    int my_unsetenv_builtin(term_t *term);
    int my_setenv_builtin(term_t *term);
    int my_print_env(term_t *term);
    void my_exit(term_t *term);

    static const struct commands_s commands[] = {
        {"cd", my_cd},
        {"exit", my_exit},
        {"env", (void *) my_print_env},
        {"setenv", (void *) my_setenv_builtin},
        {"unsetenv", (void *) my_unsetenv_builtin},
        {NULL, NULL}
    };

    char **my_str_to_word_array(char *str, const char to_clean);
    int len_tab(char **tab);

    int is_builtins(term_t *term);
    int is_executable(term_t *term);

#endif /* !MY_H_ */
