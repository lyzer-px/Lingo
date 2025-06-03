#include <stdio.h>
#include <stddef.h>

const char *GAME_PROMPT = "*: invalid letter\n"
    "?: incorrectly placed letter\n"
    "Will you find the secret word?\n";

static void blur(char const *secret_word)
{
    putchar(secret_word[0]);
    for (size_t i = 1; secret_word[i]; i++)
        putchar('*');
    puts("\n");
}

void print_prompt(char const *secret_word)
{
    printf("%s", GAME_PROMPT);
    blur(secret_word);
}
