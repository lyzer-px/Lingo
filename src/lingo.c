/*
** EPITECH PROJECT, 2024
** Lingo
** File description:
** lingo.c
*/

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "stdlib.h"
#include "lingo.h"

static size_t get_depth(char *const *tab)
{
    size_t i;

    for (i = 0; tab[i]; i++);
    return i;
}

static void blur(char const *to_guess)
{
    putchar(to_guess[0]);
    for (size_t i = 1; to_guess[i]; i++)
        putchar('*');
    puts("\n");
}

static void print_prompt(char const *to_guess)
{
    printf("%s", GAME_PROMPT);
    blur(to_guess);
}

static bool show_matches(char const *input, char const *to_guess)
{
    char *buf = strdup(input);
    puts(buf);
    return false;
}

static bool right_guess(char const *inupt, char const *to_guess)
{
    if (strcmp(inupt, to_guess) == 0)
        return true;
    else
        return show_matches(inupt, to_guess);
}

static void invalid_length(unsigned id)
{
    printf("Word too %s. Retry\n", id == 0 ? "short" : "long");
}

static int handle_user_input(char **user_input, size_t to_guess_len)
{
    size_t status = 0;
    size_t len = 0;

    if (getline(user_input, &status, stdin) < 0 ||
            strlen(*user_input) - 1 != to_guess_len) {
        len = strlen(*user_input);
        status = len - 1 < to_guess_len ? 0 : 1;
        invalid_length(status);
        return EXIT_FAILURE;
    }
    len = strlen(*user_input);
    (*user_input)[len - 1] = '\0';
    return EXIT_SUCCESS;
}

static int start_game(char const *to_guess)
{
    size_t to_guess_len = strlen(to_guess);
    size_t attempts = to_guess_len;
    char *user_input = NULL;
    bool retry = false;

    print_prompt(to_guess);
    for (size_t current_try = 1; current_try != attempts + 1;) {
        if (!retry)
            current_try += !!printf("Round %ld\n", current_try);
        printf("> ");
        if (handle_user_input(&user_input, to_guess_len) == EXIT_FAILURE) {
            retry = true;
            continue;
        }
        if (right_guess(user_input, to_guess))
            return !printf("\nYou won!\n");
        retry = false;
    }
    return !printf("\nYou lost!\n");
}

int lingo(char const *filepath)
{
    char **words = file_to_word_array(filepath);
    char *to_guess = nullptr;

    srand(time(nullptr));
    if (words == nullptr || *words == nullptr)
        return EXIT_FAIL;
    to_guess = words[rand() % get_depth(words)];
    return start_game(to_guess) | free_array(words);
}
