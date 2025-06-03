/*
** EPITECH PROJECT, 2024
** Lingo
** File description:
** nfree.c
*/

#include <stdlib.h>

void *nfree(void *ptr)
{
    free(ptr);
    return nullptr;
}
