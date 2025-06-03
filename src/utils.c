#include <stddef.h>

size_t get_depth(char *const *tab)
{
    size_t i;

    for (i = 0; tab[i]; i++);
    return i;
}
