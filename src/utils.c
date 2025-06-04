#include <stddef.h>
#include <stdio.h>

size_t get_depth(char *const *tab)
{
    size_t i;

    for (i = 0; tab[i]; i++);
    return i;
}

void invalid_length(unsigned int id)
{
    printf("Word too %s. Retry\n", id == 0 ? "short" : "long");
}
