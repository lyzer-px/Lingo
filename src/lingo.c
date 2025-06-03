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

static void blur(char const *secret_word)
{
    putchar(secret_word[0]);
    for (size_t i = 1; secret_word[i]; i++)
        putchar('*');
    puts("\n");
}

static void print_prompt(char const *secret_word)
{
    printf("%s", GAME_PROMPT);
    blur(secret_word);
}

static bool show_matches(char const *guess, char const *secret_word)
{
    size_t len = strlen(guess);
    char buf[len + 1];
    unsigned used_letter[len] = {};

    memset(buf, INVALID_CHAR, len);
    buf[len] = '\0';
    for (size_t i = 0; i < len; i++) {
        if (guess[i] == secret_word[i]) {
            buf[i] = guess[i];
            used_letter[i] = 1;
        }
    }
    for (size_t i = 0; i < len; i++) {
        if (buf[i] != INVALID_CHAR)
            continue;
        for (size_t j = 0; j < len; j++) {
            if (!used_letter[j] && guess[i] == secret_word[j]) {
                buf[i] = MISPLACED_CHAR;
                used_letter[j] = 1;
                break;
            }
        }
    }
    return!printf("%s\n", buf);
}

static bool right_guess(char const *inupt, char const *secret_word)
{
    if (strcmp(inupt, secret_word) == 0)
        return true;
    else
        return show_matches(inupt, secret_word);
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

static int start_game(char const *secret_word)
{
    size_t to_guess_len = strlen(secret_word);
    size_t attempts = to_guess_len;
    char *user_input = NULL;
    bool retry = false;

    print_prompt(secret_word);
    for (size_t current_try = 1; current_try != attempts + 1;) {
        if (!retry)
            current_try += !!printf("Round %ld\n", current_try);
        printf("> ");
        if (handle_user_input(&user_input, to_guess_len) == EXIT_FAILURE) {
            retry = true;
            continue;
        }
        if (right_guess(user_input, secret_word))
            return !printf("\nYou won!\n");
        retry = false;
    }
    return !printf("\nYou lost!\n");
}

int lingo(char const *filepath)
{
    char **words = file_to_word_array(filepath);
    char *secret_word = nullptr;

    srand(time(nullptr));
    if (words == nullptr || *words == nullptr)
        return EXIT_FAIL;
    secret_word = words[rand() % get_depth(words)];
    return start_game(secret_word) | free_array(words);
}
