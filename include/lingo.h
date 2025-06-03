/*
** EPITECH PROJECT, 2024
** Lingo
** File description:
** lingo.h
*/

#ifndef LINGO_H
    #define LINGO_H

    #define EXIT_FAIL 84
    #define INVALID_CHAR '*'
    #define MISPLACED_CHAR '?'

extern const char *GAME_PROMPT;

void *nfree(void *ptr);
int free_array(char **array);
int lingo(char const *filepath);
char **file_to_word_array(char const *filepath);
char **my_strsplt(char const *str, char delim);
#endif
