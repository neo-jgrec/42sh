/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** my_alias.c
*/

#include "my.h"
#include "list.h"
#include <string.h>

int is_sentence(char const *str);

static int print_alias(linked_list_t *alias)
{
    struct linked_list_node *node;
    alias_t *alias_struct;

    if (alias == NULL)
        return (0);
    TAILQ_FOREACH(node, &alias->head, nodes) {
        alias_struct = node->data;
        if (alias_struct->status == 1)
            my_printf("%s\t(%s)\n", ((alias_t *)alias_struct)->command[0],
            ((alias_t *)alias_struct)->command[1]);
        else
            my_printf("%s\t%s\n", ((alias_t *)alias_struct)->command[0],
            ((alias_t *)alias_struct)->command[1]);
    }
    return (0);
}

static int get_alias(char **args, linked_list_t *alias)
{
    struct linked_list_node *node;
    alias_t *alias_struct;

    TAILQ_FOREACH(node, &alias->head, nodes) {
        alias_struct = node->data;
        if (strcmp(((alias_t *)alias_struct)->command[0], args[1]) == 0 &&
            ((alias_t *)alias_struct)->status == 1) {
            my_printf("%s\t(%s)\n", ((alias_t *)alias_struct)->command[0],
            ((alias_t *)alias_struct)->command[1]);
        } else if (strcmp(((alias_t *)alias_struct)->command[0],
                args[1]) == 0) {
                my_printf("%s\t%s\n", ((alias_t *)alias_struct)->command[0],
                ((alias_t *)alias_struct)->command[1]);
        }
    }
    return (0);
}

static int check_if_existing(char **args, linked_list_t *alias, int status)
{
    linked_list_node_t *node;
    alias_t *alias_struct;

    TAILQ_FOREACH(node, &alias->head, nodes) {
        alias_struct = node->data;
        if (strcmp(((alias_t *)alias_struct)->command[0], args[1]) == 0) {
            ((alias_t *)alias_struct)->command[0] = my_strdup(args[1]);
            ((alias_t *)alias_struct)->command[1] = my_strdup(args[2]);
            ((alias_t *)alias_struct)->command[2] = NULL;
            ((alias_t *)alias_struct)->status = status;
            return (1);
        }
    }
    return (0);
}

static int add_alias(char **args, linked_list_t *alias,
alias_t *alias_struct, int status)
{
    if (strcmp(args[1], "alias") == 0) {
        my_printf("alias: Too dangerous to alias that.\n");
        return (84);
    }
    if (alias_struct->command == NULL || alias == NULL)
        return (84);
    alias_struct->command[0] = my_strdup(args[1]);
    alias_struct->command[1] = my_strdup(args[2]);
    alias_struct->command[2] = NULL;
    alias_struct->status = status;
    if (check_if_existing(args, alias, status) == 1)
        return (0);
    ll_add_node_head(alias, alias_struct);
    return (0);
}

static int create_multi_word_alias(char **args, linked_list_t *alias,
alias_t *alias_struct)
{
    char *com = my_strdup(args[2]);

    if (com == NULL || alias == NULL)
        return (84);
    for (int i = 3; args[i] != NULL; i++) {
        com = my_strcat_inf(2, com, " ");
        com = my_strcat_inf(2, com, args[i]);
        com = my_strcat_inf(2, com, "\0");
    }
    args[2] = strdup(com);
    add_alias(args, alias, alias_struct, alias_struct->status);
    return (0);
}

int my_alias(char **args, UNUSED char **env, int *exit_status,
void *data)
{
    term_t *term = (term_t *)data;
    alias_t *alias_struct = malloc(sizeof(alias_t));

    if (alias_struct == NULL) return (84);
    alias_struct->command = malloc(sizeof(char *) * 3);
    alias_struct->status = 0;
    if (term->alias == NULL)
        term->alias = ll_init_linked_list();
    if (term->ac == 1)
        *exit_status = print_alias(term->alias);
    if (term->ac == 2)
        *exit_status = get_alias(args, term->alias);
    if (term->ac == 3)
        *exit_status = create_multi_word_alias(args,
            term->alias, alias_struct);
    if (term->ac > 3) {
        alias_struct->status = 1;
        *exit_status = create_multi_word_alias(args,
            term->alias, alias_struct);
    }
    return *exit_status;
}
