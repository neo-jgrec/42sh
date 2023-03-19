/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** exec
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

// static const struct commands_s commands[] = {
//     {"cd", my_cd},
//     {"exit", my_exit},
//     {"env", (void *) my_print_env},
//     {"setenv", (void *) my_setenv_builtin},
//     {"unsetenv", (void *) my_unsetenv_builtin},
//     {NULL, NULL}
// };

// // Helper function to check if a command is a builtin
// int is_builtin(const char *cmd) {
//     for (int i = 0; commands[i].name != NULL; i++) {
//         if (strcmp(commands[i].name, cmd) == 0) {
//             return 1;
//         }
//     }
//     return 0;
// }

// // Function to execute builtin commands
// void execute_builtin(char **args, char **env) {
//     for (int i = 0; commands[i].name != NULL; i++) {
//         if (strcmp(commands[i].name, args[0]) == 0) {
//             commands[i].func(args, env);
//             break;
//         }
//     }
// }


// int main(void)
// {
//     char *args[] = {"/usr/bin/ls", "-l", "|", "/usr/bin/wc", "-l", ";", "ls", NULL};
//     char *env[] = {NULL};
//     function here
//     return 0;
// }

// static const struct commands_s commands[] = {
//     {"cd", my_cd},
//     {"exit", my_exit},
//     {"env", (void *) my_print_env},
//     {"setenv", (void *) my_setenv_builtin},
//     {"unsetenv", (void *) my_unsetenv_builtin},
//     {NULL, NULL}
// };

// make the execute function with execeve, it'll work like a bash shell taking the arguments and the environment
// Make the redirections and pipes work. you have to handle : "<", ">", "<<", ">>", "|", ";"
// Make the builtins work (cd, exit, env, setenv, unsetenv) are pointers to functions
// use only execve, fork, waitpid, dup2, open, close, pipe, dup, dup3, getcwd, chdir, opendir, readdir, closedir, stat, lstat, fstat, get_next_line, malloc, free, perror, strerror, exit
// it must have error handling for segv and unknown commands