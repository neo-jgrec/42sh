/*
** EPITECH PROJECT, 2023
** parsing
** File description:
** parsing
*/

#ifndef PARSING_
    #define PARSING_

    #define IS_RDOUT(args) my_strcmp(args, ">") == 0
    #define IS_RDIN(args) my_strcmp(args, "<") == 0
    #define IS_DRDIN(args) my_strcmp(args, "<<") == 0
    #define IS_DRDOUT(args) my_strcmp(args, ">>") == 0
    #define IS_VAR(args) my_strncmp(args, "$", 1) == 0

#endif /* !PARSING_ */
