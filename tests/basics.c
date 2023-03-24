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

    cr_assert_eq(is_executable(&environ, args), 0);
    free(environ);
}

Test(basics, m_is_builtin, .init = cr_redirect_stdout)
{
    char *args[] = {"env", NULL};

    cr_assert_eq(is_builtin(args), 0);
}
