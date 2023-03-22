/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** error_handling
*/

#include "my.h"

void perror_exit(const char *s)
{
    perror(s);
    exit(EXIT_FAILURE);
}

void sigsegv_handler(int sig)
{
    write(2, "Segmentation fault\n", 19);
    exit(EXIT_FAILURE);
}
