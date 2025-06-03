#include <stdlib.h>
#include <stdio.h>
#include "lingo.h"

int main(int ac, char **av)
{
    if (ac != 2)
        return EXIT_FAIL + !printf("Usage: ./lingo [filepath]\n");
    return lingo(av[1]);
}
