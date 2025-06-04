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
bool bfree(void *ptr);
size_t get_depth(char *const *tab);
void print_prompt(char const *secret_word);
int free_array(char **array);
void invalid_length(unsigned int id);
int lingo(char const *filepath);
char **file_to_word_array(char const *filepath);
char **my_strsplt(char const *str, const char delim);
#endif
