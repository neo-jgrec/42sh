/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** heredoc
*/

#include "my.h"

void heredoc_pipe(int *pipefd)
{
    if (pipe(pipefd) < 0) {
        perror_exit("heredoc pipe");
    }
}

void heredoc_fork(pid_t *pid)
{
    *pid = fork();
    if (*pid < 0) {
        perror_exit("heredoc fork");
    }
}

void heredoc_child(int *pipefd, char **args, int *i)
{
    char *buffer = malloc(sizeof(char) * 4096);
    char *delimiter = args[*i + 1];
    char *line = NULL;
    size_t line_len = 0;
    ssize_t read_len = 0;

    close(pipefd[0]);
    while (1) {
        printf("? ");
        read_len = getline(&line, &line_len, stdin);
        if (read_len < 0)
            break;
        line[read_len - 1] = '\0';
        if (my_strcmp(line, delimiter) == 0)
            break;
        buffer = my_strcat_inf(3, buffer, line, "\n");
    }
    write(pipefd[1], buffer, my_strlen(buffer));
    close(pipefd[1]);
    exit(0);
}

void heredoc_parent(int *pipefd, int *input_fd, char **args, int *i)
{
    close(pipefd[1]);
    *input_fd = pipefd[0];
    args[*i] = NULL;
    ++(*i);
}

void heredoc(char **args, int *input_fd, int *i)
{
    int pipefd[2];
    pid_t pid;

    heredoc_pipe(pipefd);
    heredoc_fork(&pid);
    if (pid == 0)
        heredoc_child(pipefd, args, i);
    heredoc_parent(pipefd, input_fd, args, i);
}
