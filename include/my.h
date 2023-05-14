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
    #include <aio.h>
    #include <stdbool.h>
    #include <sys/queue.h>
    #include <string.h>

    #define IS_QUOTE(c) (c == '"' || c == '\'')
    #define IS_SPACE(c) (c == ' ')

    #define BUFFER_SIZE 4096

    typedef struct history_s {
        char **command;
        char *time;
        int pos;
        struct history_s *next;
        struct history_s *prev;
    } history_t;

    typedef struct {
        history_t *head;
        history_t *tail;
        size_t size;
    } history_list_t;

    typedef struct pid_list_s {
        pid_t pid;
        TAILQ_ENTRY(pid_list_s) entries;
    } pid_list_t;

    typedef struct {
        char *str;
        char **argv;
        char **env;
        int *exit_status;
        history_list_t *history;
        char **var;
        int last_return;
        bool is_from_path;
        TAILQ_HEAD(pid_list_head_s, pid_list_s) pid_list;
    } term_t;

    struct handler_args_s {
        char *str;
        struct termios *orig_termios;
        size_t *index;
        char *c;
    };

    typedef struct {
        int *input_fd;
        int *output_fd;
    } my_fd_t;

    typedef struct commands_s {
        char *name;
        void (*func)(void *args, char **env, int *exit_status, void *data);
    } commands_t;

    typedef struct {
        int input_fd;
        int output_fd;
        int cmd_start;
        int append;
        pid_t last_pid;
    } exec_t;

    typedef struct {
        char *name;
        char *dollar_ptr;
        char *value;
        size_t prefix_len;
        size_t value_len;
    } construct_result_params_t;

    typedef struct {
        char **tokens;
        char *token;
        char *save_ptr;
        int j;
        int in_quotes;
    } tokenize_params_t;

    char *my_getenv(char **env, const char *name);
    int my_setenv(char *name, char *value, char **env);
    int my_unsetenv(char *str, char **env);
    int my_set(char *name, char *value, char ***var);
    int my_unset(char *name, char ***var);

    void my_cd(char **args, char **env, int *exit_status, UNUSED void *data);
    int my_unsetenv_builtin(char **args, char **env, int *exit_status,
    UNUSED void *data);
    int my_setenv_builtin(char **args, char **env, int *exit_status,
    UNUSED void *data);
    int my_env(char **args, char **env, int *exit_status, UNUSED void *data);
    void my_exit(char **args, char **env, int *exit_status, UNUSED void *data);
    char *my_echo(char **argv, char **env, int *exit_status,
    UNUSED void *data);
    void builtin_list(char **args, char **env, int *exit_status,
    UNUSED void *data);
    int my_which(char **args, char **env, int *exit_status, UNUSED void *data);
    int my_where(char **args, char **env, int *exit_status, UNUSED void *data);
    int my_history(char **args, char **env, int *exit_status, void *data);
    int my_unset_builtin(char **args, UNUSED char **env, int *exit_status,
    void *data);
    int my_set_builtin(char **args, UNUSED char **env, int *exit_status,
    void *data);

    static const struct commands_s commands[] = {
        {"cd", (void *) my_cd},
        {"setenv", (void *) my_setenv_builtin},
        {"unsetenv", (void *) my_unsetenv_builtin},
        {"env", (void *) my_env},
        {"exit", (void *) my_exit},
        {"echo", (void *) my_echo},
        {"builtins", (void *) builtin_list},
        {"which", (void *) my_which},
        {"where", (void *) my_where},
        {"history", (void *) my_history},
        {"set", (void *) my_set_builtin},
        {"unset", (void *) my_unset_builtin},
        {NULL, NULL}
    };

    char **my_str_to_word_array(char *str, const char to_clean);
    int len_tab(char **tab);
    bool my_str_isalphanum(char *str);
    bool my_str_isnum(char *str);

    void sigsegv_handler(term_t *term);
    void perror_exit(const char *s);
    void remove_element_at_index(char **args, int index);

    int is_executable(char ***args, char **env, term_t *term);
    bool error_variable(char **args, term_t *term);
    int is_builtins(char **args);
    int execute_builtin_command(char **args, char **env,
    term_t *term, my_fd_t fd);
    int execute_non_builtin_command(char **args, my_fd_t fd,
    char **env, term_t *term);

    void my_left_redirection(char **args, int *input_fd, int *i);
    void my_right_redirection(char **args, int *output_fd, int *i, int append);
    int my_pipe(exec_t *exec, int *i, term_t *term, char **args);
    void my_semicolon(exec_t *exec, int *i, term_t *term, char **args);
    void my_and(exec_t *exec, int *i, term_t *term, char **args);
    void my_or(exec_t *exec, int *i, term_t *term, char **args);

    history_list_t *init_history_list(void);
    void destroy_history(history_list_t *list);
    void create_history_node(history_list_t *list, char **command);
    void rm_history_node(history_t *node, history_list_t *list);
    void store_history(history_list_t *history);

    void manage_history(history_list_t *list, char **command);
    void command_is_in_history(char **command, history_list_t *list);
    char **convert_args(char **args, history_list_t *list, bool is_num);
    void display_history(history_list_t *list);
    void display_command_array(char **command);

    int exec_history_display(char **args, history_list_t *list);
    int exec_history_command(char **args, history_list_t *list, term_t *term);
    bool is_existant_event(char *str, history_list_t *list);
    char **convert_args(char **args, history_list_t *list, bool is_num);

    void display_variables(char **var, history_list_t *history);

    int check_parenthesis(term_t *term);
    void my_parenthesis(exec_t *exec, int *i, term_t *term, char **args);

#endif /* !MY_H_ */
