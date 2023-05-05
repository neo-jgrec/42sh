/*
** EPITECH PROJECT, 2023
** array
** File description:
** array
*/

#ifndef ARRAY_
    #define ARRAY_

    #include <sys/types.h>

    /**
     * @brief my_count_array_size function count the number of string
     * that contain 'array'
     *
     * @param array: The array you want to count the size.
     * @return size of the array (size_t).
    */
    size_t my_count_array_size(const char **array);

    /**
     * @brief my_create_str_array function create a new allocated array
     * filled of NULL strings;
     *
     * @param size: the number of string you want to allocate
     * @return an array allocated with the number of string 'size' (char**)
     * NULL in case of error.
    */
    char **my_create_str_array(size_t size);

    /**
     * @brief my_destroy_str_array function free the content of a string array
     * 'array' and the array itself.
     *
     * @param array The array you want to destroy.
     * @return Nothing.
    */
    void my_destroy_str_array(char **array);

    /**
     * @brief my_dup_array is a function that duplicate a string array 'array'
     * and it's content and return it.
     *
     * @param array The array you want to duplicate.
     * @return A new allocated array that is the same as 'array' (char**).
     * NULL in case of error.
    */
    char **my_dup_array(const char **array);

    char **my_copy_array(char **array_dest, const char **array_src);

    char **my_add_str_to_array(char **array, const char *str);

#endif /* !ARRAY_ */
