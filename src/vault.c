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