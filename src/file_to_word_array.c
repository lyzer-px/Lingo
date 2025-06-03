/*
** EPITECH PROJECT, 2024
** Lingo
** File description:
** file_to_word_array.c
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include "lingo.h"

int free_array(char **array)
{
    for (size_t i = 0; array[i]; i++)
        free(array[i]);
    free(array);
    return 0;
}

char **file_to_word_array(char const *filepath)
{
    int fd = open(filepath, O_RDONLY);
    struct stat stafbuff = {};
    ssize_t size = 0;
    char *buff = nullptr;
    char **array = nullptr;

    if (fd < 0 || stat(filepath, &stafbuff) < 0)
        return nullptr;
    size = stafbuff.st_size;
    buff = malloc(sizeof(char) * (size + 1));
    if (buff == nullptr)
        return nullptr;
    if (read(fd, buff, size) != size)
        return nfree(buff);
    array = my_strsplt(buff, '\n');
    free(buff);
    if (array == nullptr)
        return nullptr;
    return array;
}
