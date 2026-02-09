#include <stdio.h>
#include <string.h>
#include "vault.h"

int main(int argc, char *argv[]) {

    // Require a command to avoid reading argv[1] when it doesn't exist.
    if (argc < 2) {
        vault_help();
        return 1;
    }

    if (strcmp(argv[1], "help") == 0) {
        vault_help();
        return 0;
    }

    if (strcmp(argv[1], "init") == 0) {
        vault_init();
        return 0;
    }

    printf("Unknown command: %s\n", argv[1]);
    return 1;
}