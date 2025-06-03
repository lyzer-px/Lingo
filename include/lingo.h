/*
** EPITECH PROJECT, 2024
** Lingo
** File description:
** lingo.h
*/

#ifndef LINGO_H
    #define LINGO_H

    #define EXIT_FAIL (84)
    #define INVALID_CHAR ('*')
    #define MISPLACED_CHAR ('?')
    #define ALPHA_NBR (26)
    #define TO_INT(c) ((c) - 'a')

extern const char *GAME_PROMPT;

typedef struct game_content_s {
    char const *secret_word;
    char const *guess;
    size_t guess_len;
} game_content_t;

void *nfree(void *ptr);
ssize_t index_of(char const *str, char c);
int free_array(char **array);
int lingo(char const *filepath);
char **file_to_word_array(char const *filepath);
char **my_strsplt(char const *str, char delim);
#endif
