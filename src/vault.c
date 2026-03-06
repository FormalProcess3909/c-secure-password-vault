/*
 * vault.c
 *
 * Implements user-facing vault command handlers such as help and init.
 *
 * Responsibilities:
 * - Provide CLI command functionality.
 * - Initialize vault storage and directory structure.
 *
 * Security Boundaries:
 * - Command handlers must not expose or print credential data.
 * - Vault initialization creates storage with restricted permissions.
 * - Existing vault files must never be overwritten automatically.
 *
 * Assumptions:
 * - Vault storage resides in the local "data/" directory.
 * - Additional encryption and credential handling will be implemented in separate modules.
 */

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include "vault.h"

/*
 * Print a startup banner.
 *
 * Security note: prints only static text.
 */

void vault_banner() {
    printf("Secure Password Vault\n");
}

/*
 * Print CLI usage instructions.
 *
 * Security note: prints only static strings and does not access vault storage.
 */
void vault_help() {
    printf("Usage: vault <command>\n");
    printf("Commands:\n");
    printf("  help\n");
    printf("  init\n");
    printf("  add\n");
    printf("  list\n");
}

/*
 * Initialize vault storage.
 *
 * Behavior:
 * - Creates the "data/" directory if it does not exist.
 * - Creates an empty vault database file.
 * - Prevents overwriting existing vault storage.
 *
 * Security Notes:
 * - Directory is created with owner-only permissions (0700).
 * - This function does not store credentials or encryption keys.
 */

void vault_init() {

    const char *dir = "data";
    const char *file = "data/vault.db";

    // Attempt to create data directory
    if (mkdir(dir, 0700) == -1) {
        if (errno != EEXIST) {
            printf("Error creating data directory: %s\n", strerror(errno));
            return;
        }
    }

    // Check if vault file already exists
    FILE *fp = fopen(file, "r");
    if (fp != NULL) {
        fclose(fp);
        printf("Vault already initialized.\n");
        return;
    }

    // Create vault file
    fp = fopen(file, "w");
    if (fp == NULL) {
        printf("Error creating vault file: %s\n", strerror(errno));
        return;
    }

    fclose(fp);

    printf("Vault initialized successfully.\n");
}

/*
 * Add a credential entry to the vault database.
 *
 * Expected CLI usage:
 *   vault add <service> <username> <password>
 *
 * Behavior:
 * - Validates the number of arguments provided.
 * - Opens the vault database file in append mode.
 * - Writes the credential as a single line in the format:
 *
 *   service|username|password
 *
 * Security Note:
 * Credentials are currently stored in plaintext. Future versions
 * of the vault will encrypt stored entries before writing them.
 */

void vault_add(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: vault add <service> <username> <password>\n");
        return;
    }

    char *service = argv[2];
    char *username = argv[3];
    char *password = argv[4];

    FILE *fp = fopen("data/vault.db", "a");

    if (fp == NULL) {
        printf("Error: could not open vault database\n");
        return;
    }

    fprintf(fp, "%s|%s|%s\n", service, username, password);

    fclose(fp);

    printf("Credential added successfully\n");
}

/*
 * Display stored credentials from the vault database.
 *
 * Behavior:
 * - Opens the vault database file in read mode.
 * - Reads entries line-by-line until EOF.
 * - Prints each line exactly as stored in the database.
 *
 * Stored credential format:
 *   service|username|password
 *
 * Security Note:
 * Credentials are currently stored in plaintext. Future versions
 * of the vault will encrypt stored entries before writing them.
 */

void vault_list() {
    FILE *fp = fopen("data/vault.db", "r");

    if (fp == NULL) {
        printf("Error: could not open vault database\n");
        return;
    }

    char line[256];

    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }

    fclose(fp);
}