/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** parenthese handing
*/

#include "my.h"
#include <sys/wait.h>

int execute_commands(char **args, term_t *term);

char **extract_commands_in_parentheses(char **args, int *i)
{
    int j = 0;
    char **subshell_args = malloc(sizeof(char *) * 100);
    int parentheses_count = 0;

    (*i)++;
    while (args[*i] != NULL) {
        if (strcmp(args[*i], "(") == 0)
            parentheses_count++;
        if (strcmp(args[*i], ")") == 0 && parentheses_count == 0)
            break;
        if (strcmp(args[*i], ")") == 0 && parentheses_count > 0)
            parentheses_count--;
        subshell_args[j] = strdup(args[*i]);
        j++;
        (*i)++;
    }

    subshell_args[j] = NULL;
    return subshell_args;
}

void my_parenthesis(UNUSED exec_t *exec, int *i, term_t *term, char **args)
{
    int pid, status;
    char **subshell_args;

    if (args[*i + 1] == NULL || strcmp(args[*i + 1], ")") == 0) {
        dprintf(2, "Missing command for subshell.\n");
        remove_element_at_index(args, *i);
        return;
    }
    subshell_args = extract_commands_in_parentheses(args, i);
    if ((pid = fork()) < 0) {
        perror_exit("fork");
    } else if (pid == 0) {
        execute_commands(subshell_args, term);
        exit(0);
    } else
        waitpid(pid, &status, 0);
    (*i) += 1;
    exec->cmd_start = *i + 1;
    free(subshell_args);
}
