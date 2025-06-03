#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

ssize_t index_of(char const *str, char c)
{
    ssize_t check = 0;

    for (size_t i = 0; str[i]; i++)
        check += str[i] == c;
    return check ? check : -1;
}

static size_t count_delims(char const *str, char delim)
{
    size_t count = 0;

    for (size_t i = 0; str[i]; i++)
        count += str[i] == delim;
    return count;
}

static size_t next_word_len(char const *str, char delim)
{
    size_t i = 0;

    for (; str[i] && str[i] != delim; i++);
    return i;
}

static void end_string(size_t *k, char *adr, size_t *j)
{
    (*k)++;
    *adr = '\0';
    *j = 0;
}

char **my_strsplt(char const *str, char delim)
{
    size_t size = count_delims(str, delim);
    char **array = malloc(sizeof(char *) * (size + 2));
    size_t j = 0;
    size_t k = 0;
    size_t i = 0;

    if (array == nullptr)
        return nullptr;
    for (; i < size; i++) {
        array[i] = malloc(sizeof(char) * (next_word_len(str + k, delim) + 1));
        if (array[i] == nullptr)
            return nullptr;
        for (; str[k] != delim && str[k]; j++) {
            array[i][j] = str[k];
            k++;
        }
        end_string(&k, &(array[i][j]), &j);
    }
    array[size] = nullptr;
    return array;
}
