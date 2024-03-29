/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** my_cd
*/

#include "my.h"
#include <string.h>

static void cd_error(char *message, int *exit_status)
{
    dprintf(2, "%s.\n", message);
    *exit_status = 1;
}

static void error_handling(char **argv, char **env, char *pwd,
int *exit_status)
{
    if (errno != 0) {
        dprintf(2, "%s: %s.\n", argv[1], strerror(errno));
        *exit_status = 1;
        errno = 0;
    } else {
        my_setenv("OLDPWD", pwd, env);
        my_setenv("PWD", getcwd(NULL, 0), env);
    }
}

void my_cd(char **argv, char **env, int *exit_status, UNUSED void *data)
{
    char *home = my_getenv(env, "HOME");
    char *oldpwd = my_getenv(env, "OLDPWD");
    char *pwd = getcwd(NULL, 0);
    errno = 0;
    *exit_status = 0;
    if (argv[1] == NULL) {
        if (home == NULL) {
            cd_error("cd: No home directory", exit_status);
            return;
        } else
            chdir(home);
    } else if (my_strcmp(argv[1], "-") == 0) {
        (oldpwd == NULL) ? ({
            cd_error(": No such file or directory", exit_status);
            return;
        }) : (0);
        chdir(oldpwd);
    } else
        chdir(argv[1]);
    error_handling(argv, env, pwd, exit_status);
}
