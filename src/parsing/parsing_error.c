/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** parsing_error
*/

#include "parsing.h"
#include "my.h"

int is_there_only_char(char **args, char *to_find)
{
    for (int i = 0; args[i] != NULL; i++) {
        if (my_strcmp(args[i], to_find) != 0)
            return (0);
    }
    return (1);
}

int all_char_check(char **args)
{
    if (my_strcmp(args[0], "|") == 0 && args[1] == NULL) {
        dprintf(2, "Invalid null command.\n");
        return (1);
    }
    if (is_there_only_char(args, ">") || is_there_only_char(args, "<") ||
    is_there_only_char(args, ">>") || is_there_only_char(args, "<<")
    || is_there_only_char(args, "|") || is_there_only_char(args, ";"))
        return (1);
    if ((my_strcmp(args[0], ">") == 0 || my_strcmp(args[0], "<") == 0
    || my_strcmp(args[0], ">>") == 0 || my_strcmp(args[0], "<<") == 0)
    && args[1] == NULL)
        return (1);
    return (0);
}

void handle_exit(char **args, int i)
{
    if (my_strcmp(args[i], "exit") == 0 &&
        (i == 0 || my_strcmp(args[i - 1], ";") == 0) &&
        (args[i + 1] == NULL || my_strcmp(args[i + 1], ";") == 0)) {
        if (i > 0 && my_strcmp(args[i - 1], ";") == 0) {
            remove_element_at_index(args, i - 1);
            i--;
        }
        remove_element_at_index(args, i);
        int end_index;
        for (end_index = 0; args[end_index] != NULL; end_index++);
        args[end_index] = my_strdup(";");
        args[end_index + 1] = my_strdup("exit");
        args[end_index + 2] = NULL;
    }
}

int parsing_error(char **args, term_t *term)
{
    if (!my_strcmp(args[0], ";"))
        remove_element_at_index(args, 0);
    for (int i = 0; args[i + 1] != NULL; i++) {
        if (((IS_RDOUT(args[i]) || IS_RDIN(args[i])) && (IS_RDOUT(args[i + 1])
        || IS_RDIN(args[i + 1]))) || ((IS_DRDOUT(args[i]) || IS_DRDIN(args[i]))
        && (IS_DRDOUT(args[i + 1]) || IS_DRDIN(args[i + 1])))) {
            dprintf(2, "Missing name for redirect.\n");
            return (1);
        }
        if (my_strcmp(args[i], "|") == 0 && my_strcmp(args[i + 1], "|") == 0) {
            dprintf(2, "Invalid null command.\n");
            return (1);
        }
        handle_exit(args, i);
    }
    if (all_char_check(args) == 1 || error_variable(args, term))
        return (1);
    return (0);
}
