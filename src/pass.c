#include "include/pass.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned long long rdtsc() {
    unsigned int lo, hi;
    __asm__ volatile ("rdtsc" : "=a"(lo), "=d"(hi));
    return ((unsigned long long)hi << 32) | lo;
}

char *ps_generate(char* chars, pass_length length)
{
    size_t charsLength = strlen(chars);
    srand(time(NULL) + rdtsc());

    if (charsLength == 0)
    {
        fprintf(stderr, "No characters provided\n");
        exit(EXIT_FAILURE);
    }

    char *pass = malloc(length + 1);
    for (pass_length i = 0; i < length; i++)
        pass[i] = chars[rand() % charsLength];

    return pass;
}