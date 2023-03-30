/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** basics
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my.h"

Test(basics, str_to_word_array, .init = cr_redirect_stdout)
{
    char *str = "ls > test ; ls | grep test";
    char **args = my_str_to_word_array(str, ' ');

    cr_assert_str_eq(args[0], "ls");
}

Test(basics, m_getenv, .init = cr_redirect_stdout)
{
    char *name = "PATH";
    char *value = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    char **environ = malloc(sizeof(char *) * 2);
    environ[0] = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    environ[1] = "PWD=/home/epitech";
    environ[2] = NULL;

    cr_assert_str_eq(my_getenv(environ, name), value);
}

Test(basics, m_setenv, .init = cr_redirect_stdout)
{
    char *name = "PATH";
    char *value = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    char **environ = malloc(sizeof(char *) * 2);
    environ[0] = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    environ[1] = "PWD=/home/epitech";
    environ[2] = NULL;

    cr_assert_eq(my_setenv(name, value, environ), 0);
    free(environ);
}

Test(basics, m_env, .init = cr_redirect_stdout)
{
    char **environ = malloc(sizeof(char *) * 10);
    environ[0] = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    environ[1] = "PWD=/home/epitech";
    environ[2] = NULL;
    char *args[] = {"env", NULL};
    int *status = malloc(sizeof(int));
    *status = 0;

    cr_assert_eq(my_env(args, environ, status), 0);
    free(status);
    free(environ);
}

Test(basics, m_cd, .init = cr_redirect_stdout)
{
    char **environ = malloc(sizeof(char *) * 10);
    environ[0] = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    environ[1] = "PWD=/home/epitech";
    environ[2] = NULL;
    char *args[] = {"cd", NULL};
    int *status = malloc(sizeof(int));
    *status = 0;

    my_cd(args, environ, status);
    cr_assert_eq(*status, 0);
    free(status);
    free(environ);
}

Test(basics, m_str_isalphanum, .init = cr_redirect_stdout)
{
    char *str = "ls > test ; ls | grep test";

    cr_assert_eq(my_str_isalphanum(str), 0);
}

Test(basics, m_perror_exit, .init = cr_redirect_stdout)
{
    char *str = "ls";
    errno = 8;

    perror_exit(str);
    errno = 1;
    perror_exit(str);
    cr_assert_stdout_eq_str("ls: Exec format error. Wrong Architecture.\nls: Operation not permitted.\n");
}

Test(basics, m_remove_element_at_index, .init = cr_redirect_stdout)
{
    char **environ = malloc(sizeof(char *) * 10);
    environ[0] = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    environ[1] = "PWD=/home/epitech";
    environ[2] = NULL;

    remove_element_at_index(environ, 0);
    cr_assert_str_eq(environ[0], "PWD=/home/epitech");
    free(environ);
}

Test(basics, m_is_executable, .init = cr_redirect_stdout)
{
    char **environ = malloc(sizeof(char *) * 10);
    environ[0] = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    environ[1] = "PWD=/home/epitech";
    environ[2] = NULL;
    char *args[] = {"ls", NULL};

    term_t *term = malloc(sizeof(term_t));
    term->is_from_path = 0;

    cr_assert_eq(is_executable(&environ, args, term), 0);
    free(environ);
}

Test(basics, m_is_builtin, .init = cr_redirect_stdout)
{
    char *args[] = {"setenv", NULL};

    cr_assert_eq(is_builtins(args), 0);
}

Test(basics, command_echo)
{
    char *args[] = {"echo", "Hello World", NULL};
    int *status = malloc(sizeof(int));
    *status = 0;
    char **environ = malloc(sizeof(char *) * 10);
    environ[0] = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    environ[1] = "PWD=/home/epitech";
    environ[2] = NULL;

    cr_assert_eq(my_echo(args, environ, status), 0);
    free(status);
}

// char *my_getenv(char **env, const char *name);
// int my_setenv(char *name, char *value, char **env);
// int my_unsetenv(char *str, char **env);

Test(basics, m_unsetenv, .init = cr_redirect_stdout)
{
    char *name = "PATH";
    char **environ = malloc(sizeof(char *) * 2);
    environ[0] = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    environ[1] = "PWD=/home/epitech";
    environ[2] = NULL;
    my_setenv(name, "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin", environ);
    cr_assert_eq(my_unsetenv(name, environ), 0);
    free(environ);
}

// int my_which(char **args, char **env, int *exit_status);
// int my_where(char **args, char **env, int *exit_status);

Test(basics, m_which, .init = cr_redirect_stdout)
{
    char **environ = malloc(sizeof(char *) * 10);
    environ[0] = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    environ[1] = "PWD=/home/epitech";
    environ[2] = NULL;
    char *args[] = {"which", "ls", NULL};
    int *status = malloc(sizeof(int));
    *status = 0;

    cr_assert_eq(my_which(args, environ, status), 0);
    free(status);
    free(environ);
}

Test(basics, m_where, .init = cr_redirect_stdout)
{
    char **environ = malloc(sizeof(char *) * 10);
    environ[0] = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    environ[1] = "PWD=/home/epitech";
    environ[2] = NULL;
    char *args[] = {"where", "ls", NULL};
    int *status = malloc(sizeof(int));
    *status = 0;

    cr_assert_eq(my_where(args, environ, status), 0);
    free(status);
    free(environ);
}

//     void builtin_list(char **args, char **env, int *exit_status);

Test(basics, m_builtin_list, .init = cr_redirect_stdout)
{
    char **environ = malloc(sizeof(char *) * 10);
    environ[0] = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    environ[1] = "PWD=/home/epitech";
    environ[2] = NULL;
    char *args[] = {"list", NULL};
    int *status = malloc(sizeof(int));
    *status = 0;

    builtin_list(args, environ, status);
    cr_assert_eq(*status, 0);
    free(status);
    free(environ);
}

//     void my_exit(char **args, char **env, int *exit_status);

Test(basics, m_exit, .init = cr_redirect_stdout)
{
    char **environ = malloc(sizeof(char *) * 10);
    environ[0] = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    environ[1] = "PWD=/home/epitech";
    environ[2] = NULL;
    char *args[] = {"exit", NULL};
    int *status = malloc(sizeof(int));
    *status = 0;

    my_exit(args, environ, status);
    cr_assert_eq(*status, 0);
    free(status);
    free(environ);
}

Test(basics, m_exit2, .init = cr_redirect_stdout)
{
    char **environ = malloc(sizeof(char *) * 10);
    environ[0] = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    environ[1] = "PWD=/home/epitech";
    environ[2] = NULL;
    char *args[] = {"exit", "45", NULL};
    int *status = malloc(sizeof(int));
    *status = 0;

    my_cd(args, environ, status);
    cr_assert_eq(*status, 0);
    free(status);
    free(environ);
}

//     int my_env(char **args, char **env, int *exit_status);

Test(basics, m_env_x, .init = cr_redirect_stdout)
{
    char **environ = malloc(sizeof(char *) * 10);
    environ[0] = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    environ[1] = "PWD=/home/epitech";
    environ[2] = NULL;
    char *args[] = {"env", NULL};
    int *status = malloc(sizeof(int));
    *status = 0;

    cr_assert_eq(my_env(args, environ, status), 0);
    free(status);
    free(environ);
}

//    int my_setenv_builtin(char **args, char **env, int *exit_status);

Test(basics, m_setezdnv, .init = cr_redirect_stdout)
{
    char **environ = malloc(sizeof(char *) * 10);
    environ[0] = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    environ[1] = "PWD=/home/epitech";
    environ[2] = NULL;
    char *args[] = {"setenv", "PATH", "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin", NULL};
    int *status = malloc(sizeof(int));
    *status = 0;

    cr_assert_eq(my_setenv_builtin(args, environ, status), 0);
    free(status);
    free(environ);
}

Test(basics, m_setezdnvf, .init = cr_redirect_stdout)
{
    char **environ = malloc(sizeof(char *) * 10);
    environ[0] = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    environ[1] = "PWD=/home/epitech";
    environ[2] = NULL;
    char *args[] = {"setenv", "P$ATH", "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin", NULL};
    int *status = malloc(sizeof(int));
    *status = 0;

    cr_assert_eq(my_setenv_builtin(args, environ, status), 1);
    free(status);
    free(environ);
}

//    int my_unsetenv_builtin(char **args, char **env, int *exit_status);

Test(basics, m_unsetenszdv, .init = cr_redirect_stdout)
{
    char **environ = malloc(sizeof(char *) * 10);
    environ[0] = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    environ[1] = "PWD=/home/epitech";
    environ[2] = NULL;
    char *args[] = {"unsetenv", "PATH", NULL};
    int *status = malloc(sizeof(int));
    *status = 0;

    cr_assert_eq(my_unsetenv_builtin(args, environ, status), 0);
    free(status);
    free(environ);
}

//    char **my_str_to_word_array(char *str, const char to_clean);

Test(basics, m_str_to_word_array, .init = cr_redirect_stdout)
{
    char *str = "ls -l";
    char **array = my_str_to_word_array(str, ' ');

    cr_assert_str_eq(array[0], "ls");
    cr_assert_str_eq(array[1], "-l");
    cr_assert_eq(array[2], NULL);
    free(array);
}

//    int len_tab(char **tab);

Test(basics, len_tab, .init = cr_redirect_stdout)
{
    char **tab = malloc(sizeof(char *) * 3);
    tab[0] = "ls";
    tab[1] = "-l";
    tab[2] = NULL;

    cr_assert_eq(len_tab(tab), 2);
    free(tab);
}

    //bool my_str_isalphanum(char *str);

Test(basics, my_str_isalphanum, .init = cr_redirect_stdout)
{
    char *str = "ls -l";

    cr_assert_eq(my_str_isalphanum(str), false);
}

    // void my_left_redirection(char **args, int *input_fd, int *i);
    // void my_right_redirection(char **args, int *output_fd, int *i, int append);
    // int my_pipe(exec_t *exec, int *i, term_t *term, char **args);
    // void my_semicolon(exec_t *exec, int *i, term_t *term, char **args);
    // void my_and(exec_t *exec, int *i, term_t *term, char **args);
    // void my_or(exec_t *exec, int *i, term_t *term, char **args);

Test(basics, my_left_redirection, .init = cr_redirect_stdout)
{
    char **args = malloc(sizeof(char *) * 3);
    args[0] = "ls";
    args[1] = "<";
    args[2] = NULL;
    int *input_fd = malloc(sizeof(int));
    int *i = malloc(sizeof(int));

    *input_fd = 0;
    *i = 0;
    my_left_redirection(args, input_fd, i);
    cr_assert_eq(*input_fd, 0);
    cr_assert_eq(*i, 0);
    free(input_fd);
    free(i);
    free(args);
}

Test(basics, my_right_redirection, .init = cr_redirect_stdout)
{
    char **args = malloc(sizeof(char *) * 3);
    args[0] = "ls";
    args[1] = ">";
    args[2] = NULL;
    int *output_fd = malloc(sizeof(int));
    int *i = malloc(sizeof(int));

    *output_fd = 0;
    *i = 0;
    my_right_redirection(args, output_fd, i, 0);
    cr_assert_eq(*output_fd, 0);
    cr_assert_eq(*i, 0);
    free(output_fd);
    free(i);
    free(args);
}

Test(basics, my_pipe, .init = cr_redirect_stdout)
{
    char **args = malloc(sizeof(char *) * 3);
    args[0] = "ls";
    args[1] = "|";
    args[2] = NULL;
    int *i = malloc(sizeof(int));
    exec_t *exec = malloc(sizeof(exec_t));
    term_t *term = malloc(sizeof(term_t));

    *i = 0;
    cr_assert_eq(my_pipe(exec, i, term, args), 0);
    free(i);
    free(exec);
    free(term);
    free(args);
}
