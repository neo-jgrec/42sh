/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** cpy_env
*/

#include "my.h"

static size_t count_args(char **array)
{
    size_t args = 0;
    char **tmp = array;

    while (*tmp) {
        args++;
        tmp++;
    }
    return args;
}

static char **get_empty_env(void)
{
    char **env = NULL;
    char *pwd = getcwd(NULL, 0);
    size_t pwd_len = my_strlen(pwd) + 5;
    char *f_pwd = NULL;

    if ((env = malloc(sizeof(char *) * 4)) == NULL)
        return NULL;
    if ((f_pwd = malloc(sizeof(char) * pwd_len)) == NULL)
        return NULL;
    env[0] = my_strdup("PATH=/usr/local/bin:/usr/bin\
:/bin:/usr/local/sbin:/usr/sbin");
    f_pwd = my_strcat(f_pwd, "PWD=");
    f_pwd = my_strcat(f_pwd, pwd);
    env[1] = f_pwd;
    env[2] = my_strdup("SHLVL=1");
    env[3] = NULL;
    return env;
}

static char **get_env_cpy(char **env, size_t args)
{
    char **cpy = malloc(sizeof(char *) * (args + 1));
    size_t i = 0;

    if (cpy == NULL)
        return NULL;
    while (i < args) {
        cpy[i] = lb_strdup(env[i]);
        i++;
    }
    cpy[i] = NULL;
    return cpy;
}

char **cpy_env(char **env)
{
    size_t args = count_args(env);

    if (args == 0)
        return get_empty_env();
    else
        return get_env_cpy(env, args);
    return NULL;
}
