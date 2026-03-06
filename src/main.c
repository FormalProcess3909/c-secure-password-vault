/*
 * main.c
 *
 * Entry point for the vault CLI application.
 *
 * Responsibilities:
 * - Parse the first command-line argument.
 * - Route execution to the appropriate vault command handler.
 *
 * This file intentionally contains minimal logic. Most functionality
 * is implemented in vault.c to keep the CLI routing separate from
 * vault operations.
 */

#include <stdio.h>
#include <string.h>
#include "vault.h"

int main(int argc, char *argv[]) {

    // Require a command to avoid reading argv[1] when it doesn't exist.
    if (argc < 2) {
        vault_help();
        return 1;
    }

    // Route CLI commands to their corresponding handler functions.

    if (strcmp(argv[1], "help") == 0) {
        vault_help();
        return 0;
    }

    if (strcmp(argv[1], "init") == 0) {
        vault_init();
        return 0;
    }

    if (strcmp(argv[1], "add") == 0) {
        vault_add(argc, argv);
        return 0;
    }

    if (strcmp(argv[1], "list") == 0) {
        vault_list();
        return 0;
    }

    printf("Unknown command: %s\n", argv[1]);
    return 1;
}
