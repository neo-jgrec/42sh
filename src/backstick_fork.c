/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** backstick_fork
*/

#include <time.h>
#include <string.h>
#include "my.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

char *clean_str_minishell(char *str, const char *to_clean);
int execute_commands(char **args, term_t *term);
int parsing_error(char **args);
char *read_stdin(term_t *term);
char **check_str(char *str, char **args, term_t *term);
void handle_sigint_program(int sig);

static int miniminishell(term_t *term)
{
    term->argv = check_str(term->str, term->argv, term);
    if (term->argv == NULL)
        return 1;
    manage_history(term->history, term->argv);
    if (parsing_error(term->argv) == 1)
        return 1;
    signal(SIGINT, handle_sigint_program);
    execute_commands(term->argv, term);
    return 0;
}

static char *add_char(char *buff, char *reading_buf)
{
    int len = my_strlen(buff);
    char *new_buff = malloc(sizeof(char) * (len + 2));

    if (new_buff == NULL)
        return NULL;
    for (int i = 0; i < (len + 2); i++)
        new_buff[i] = '\0';
    for (int i = 0; i < len; i++)
        new_buff[i] = buff[i];
    new_buff[len] = reading_buf[0];
    free(buff);
    return new_buff;
}

char *fork_call(char *str, char *buff, term_t *term)
{
    int fd[2];
    char reading_buf[1];
    int pid = 0;
    int ret = 0;

    pipe(fd);
    if ((pid = fork()) == 0) {
        close(fd[0]);
        dup2(fd[1], 1);
        term->str = clean_str_minishell(str, " \t");
        miniminishell(term);
        exit(0);
    } else {
        close(fd[1]);
        while (read(fd[0], reading_buf, 1) > 0)
            buff = add_char(buff, reading_buf);
        close(fd[0]);
        waitpid(pid, &ret, 0);
    }
    return buff;
}
