/*
** EPITECH PROJECT, 2025
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

static void handle_correct_placements(const game_content_t *words, char *buf,
    unsigned int *used_letter)
{
    for (size_t i = 0; i < words->guess_len; i++) {
        if (words->guess[i] == words->secret_word[i]) {
            buf[i] = words->guess[i];
            used_letter[i] = 1;
        }
    }
}

static void handle_incorrect_placement(const game_content_t *words, char *buf,
    const unsigned int *used_letter, const size_t i)
{
    for (size_t j = 0; j < words->guess_len; j++) {
        if (!used_letter[j] && words->guess[i] == words->secret_word[j]) {
            buf[i] = MISPLACED_CHAR;
            break;
        }
    }
}

static bool show_matches(char const *guess, char const *secret_word)
{
    const game_content_t words = {.secret_word = secret_word,
        .guess = guess, .guess_len = strlen(guess)};
    char buf[words.guess_len + 1];
    const unsigned int used_letter[words.guess_len] = {};

    memset(buf, INVALID_CHAR, words.guess_len);
    buf[words.guess_len] = '\0';
    handle_correct_placements(&words, (char *)buf,
        (unsigned int *)used_letter);
    for (size_t i = 0; i < words.guess_len; i++) {
        if (buf[i] != INVALID_CHAR)
            continue;
        handle_incorrect_placement(&words, (char *)buf,
            (unsigned int *)used_letter, i);
    }
    return !printf("%s\n", buf);
}

static bool right_guess(char const *inupt, char const *secret_word)
{
    if (strcmp(inupt, secret_word) == 0)
        return true;
    else
        return show_matches(inupt, secret_word);
}

static int handle_user_input(char **user_input, const size_t to_guess_len)
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
    const size_t to_guess_len = strlen(secret_word);
    const size_t attempts = to_guess_len;
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
        if (right_guess(user_input, secret_word)) {
            return !printf("\nYou won!\n") | bfree(user_input);
        }
        retry = false;
    }
    return !printf("\nYou lost!\n") | bfree(user_input);
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
