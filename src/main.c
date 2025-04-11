#include "include/pass.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>
#define VERSION "1.0.0"

static void usage(const char *prog)
{
    fprintf(stderr, "Usage: %s [options]\n", prog);
    fprintf(stderr, "  -l <length>    Passphrase length (default: 16)\n");
    fprintf(stderr, "  -c <count>     Passphrase count (default: 1)\n");
    fprintf(stderr, "  -C <chars>     Additional characters\n");
    fprintf(stderr, "  -a             Add alphabet characters (default true, can be disabled with -a)\n");
    fprintf(stderr, "  -n             Add numbers characters (default true, can be disabled with -n)\n");
    fprintf(stderr, "  -s             Add special characters (default false)\n\n");
    fprintf(stderr, "  -h             Display this help message\n");
    fprintf(stderr, "  -v             Display version\n");
    exit(EXIT_FAILURE);
}
static inline void insertCharacters(char *buffer, size_t bufferSize, char *characters)
{
    if (strlen(characters) > bufferSize - strlen(buffer))
    {
        fprintf(stderr, "Too many characters\n");
        exit(EXIT_FAILURE);
    }
    strcat(buffer, characters);
}

int main(int argc, char **argv)
{
    struct {
        pass_length length;
        size_t count;
        char chars[1024];

        bool add_alphabet;
        bool add_numbers;
        bool add_special;
    } options = {
        .length = 16,
        .count = 1,
        .add_alphabet = true,
        .add_numbers = true,
        .add_special = false
    };

    memset(options.chars, 0, sizeof(options.chars));

    int opt;
    while ((opt = getopt(argc, argv, "hvl:c:C:ans")) != -1)
    {
        switch (opt)
        {
        case 'l':
            options.length = atoi(optarg);
            break;
        case 'c':
            options.count = atoi(optarg);
            break;
        case 'C':
            insertCharacters(options.chars, sizeof(options.chars), optarg);
            break;
        case 'a': options.add_alphabet = false; break;
        case 'n': options.add_numbers = false; break;
        case 's': options.add_special = true; break;
        case 'v':
            printf("EntropyKey %s by honakac (https://github.com/honakac)\n", VERSION);
            exit(EXIT_SUCCESS);
        default:
            usage(argv[0]);
        }
    }

    if (options.add_alphabet)
        insertCharacters(options.chars, sizeof(options.chars), "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    if (options.add_numbers)
        insertCharacters(options.chars, sizeof(options.chars), "0123456789");
    if (options.add_special)
        insertCharacters(options.chars, sizeof(options.chars), "!#$%&()*+,-./:;<=>?@[]^_{|}~");

    for (size_t i = 0; i < options.count; i++)
    {
        char *pass = ps_generate(options.chars, options.length);
        printf("%s\n", pass);
        free(pass);
    }
    return 0;
}