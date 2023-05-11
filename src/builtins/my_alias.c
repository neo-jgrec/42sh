/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** my_alias.c
*/

#include "my.h"
#include "list.h"
#include <string.h>

static int is_sentence(char const *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++) {
        if (str[i] == ' ')
            return 1;
    }
    return 0;
}

static int print_alias(linked_list_t *alias)
{
    struct linked_list_node *node;

    if (alias == NULL)
        return (0);
    TAILQ_FOREACH(node, &alias->head, nodes) {
        if (is_sentence(((char **)node->data)[1]))
            my_printf("%s\t(%s)\n", ((char **)node->data)[0],
            ((char **)node->data)[1]);
        else
            my_printf("%s\t%s\n", ((char **)node->data)[0],
            ((char **)node->data)[1]);
    }
    return (0);
}

static int get_alias(char **args, linked_list_t *alias)
{
    struct linked_list_node *node;

    if (alias == NULL)
        return (0);
    TAILQ_FOREACH(node, &alias->head, nodes) {
        if (strcmp(((char **)node->data)[0], args[1]) == 0) {
            if (is_sentence(((char **)node->data)[1]))
                my_printf("%s\t(%s)\n", ((char **)node->data)[0],
                ((char **)node->data)[1]);
            else
                my_printf("%s\t%s\n", ((char **)node->data)[0],
                ((char **)node->data)[1]);
        }
    }
    return (0);
}

static int add_alias(char **args, linked_list_t *alias)
{
    char **command = malloc(sizeof(char *) * 2);
    struct linked_list_node *node;

    if (command == NULL || alias == NULL)
        return (84);
    command[0] = strdup(args[1]);
    command[1] = strdup(args[2]);
    TAILQ_FOREACH(node, &alias->head, nodes) {
        if (my_strcmp(((char **)node->data)[0], args[1]) == 0) {
            ((char **)node->data)[1] = my_strdup(args[2]);
            return (0);
        }
    }
    ll_add_node_head(alias, command);
    return (0);
}

static int create_multi_word_alias(char **args, linked_list_t *alias)
{
    char *com = my_strdup(args[2]);

    if (com == NULL || alias == NULL)
        return (84);
    for (int i = 3; args[i] != NULL; i++) {
        com = strcat(com, " ");
        com = strcat(com, args[i]);
    }
    args[2] = com;
    add_alias(args, alias);
    return (0);
}

int my_alias(char **args, UNUSED char **env, int *exit_status, void *data)
{
    term_t *term = (term_t *)data;

    if (term->alias == NULL)
        term->alias = ll_init_linked_list();
    if (len_tab(args) == 1)
        *exit_status = print_alias(term->alias);
    if (len_tab(args) == 2)
        *exit_status = get_alias(args, term->alias);
    if (len_tab(args) == 3)
        *exit_status = add_alias(args, term->alias);
    if (len_tab(args) > 3)
        *exit_status = create_multi_word_alias(args, term->alias);
    else
        *exit_status = 84;
    return *exit_status;
}
