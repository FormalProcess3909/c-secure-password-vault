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
 * Check whether a vault entry line matches the requested service name.
 *
 * Behavior:
 * - Copies the input line into a temporary buffer.
 * - Extracts the first field using "|" as the delimiter.
 * - Compares the extracted service field to the requested service name.
 *
 * Returns:
 * - 1 if the service names match
 * - 0 if they do not match or the line is malformed
 *
 * Security Note:
 * The original input line is not modified. Tokenization is performed
 * on a temporary copy of the line buffer.
 */

static int service_matches(const char *line, const char *service) {
    char line_copy[256];
    strcpy(line_copy, line);

    char *token = strtok(line_copy, "|");

    if (token == NULL) {
        return 0;
    }

    return strcmp(token, service) == 0;
}

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
    printf("  get\n");
    printf("  delete\n");
    printf("  update\n");
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

/*
 * Retrieve and display a credential entry for a specific service.
 *
 * Behavior:
 * - Opens the vault database file in read mode.
 * - Reads entries line-by-line until EOF.
 * - Compares each entry's service field against the requested service name.
 * - Prints the first matching entry exactly as stored in the database.
 *
 * Returns:
 * - 0 if a matching service is found
 * - 1 if the service is not found or the database cannot be opened
 *
 * Stored credential format:
 *   service|username|password
 *
 * Security Note:
 * Credentials are currently stored and displayed in plaintext.
 * Future versions should minimize credential exposure and add encryption.
 */

int vault_get(const char *service) {
    FILE *fp = fopen("data/vault.db", "r");

    if (fp == NULL) {
        printf("Error: could not open vault database\n");
        return 1;
    }

    char line[256];

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (service_matches(line, service)) {
            printf("%s", line);
            fclose(fp);
            return 0;
        }
    }

    fclose(fp);
    printf("Service not found\n");
    return 1;
}

/*
 * Delete credential entries for a specific service.
 *
 * Behavior:
 * - Opens the vault database file in read mode.
 * - Creates a temporary file to store updated entries.
 * - Reads entries line-by-line until EOF.
 * - Skips any entry matching the requested service name.
 * - Writes all non-matching entries to the temporary file.
 * - Replaces the original database file with the temporary file if a match is found.
 *
 * Returns:
 * - 0 if at least one matching service entry is deleted
 * - 1 if the service is not found or an error occurs
 *
 * Stored credential format:
 *   service|username|password
 *
 * Security Note:
 * This operation rewrites the vault file using a temporary file to
 * avoid partial data loss in case of failure.
 */

int vault_delete(const char *service) {
    FILE *src = fopen("data/vault.db", "r");
    FILE *tmp = fopen("data/vault.tmp", "w");

    if (src == NULL) {
        printf("Error: could not open vault database\n");
        return 1;
    }

    if (tmp == NULL) {
        printf("Error: could not create temporary file\n");
        fclose(src);
        return 1;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), src) != NULL) {
        if (service_matches(line, service)) {
            found++;
            continue;
        }

        fputs(line, tmp);
    }

    fclose(src);
    fclose(tmp);

    if (found) {
        remove("data/vault.db");
        rename("data/vault.tmp", "data/vault.db");
        printf("Service deleted successfully\n");
        return 0;
    } else {
        remove("data/vault.tmp");
        printf("Service not found\n");
        return 1;
    }
}

/*
 * Update credential entries for a specific service.
 *
 * Behavior:
 * - Opens the vault database file in read mode.
 * - Creates a temporary file to store updated entries.
 * - Reads entries line-by-line until EOF.
 * - Replaces any entry matching the requested service name
 *   with a new entry containing the updated username and password.
 * - Writes all non-matching entries unchanged.
 * - Replaces the original database file with the temporary file if a match is found.
 *
 * Returns:
 * - 0 if at least one matching service entry is updated
 * - 1 if the service is not found or an error occurs
 *
 * Stored credential format:
 *   service|username|password
 *
 * Security Note:
 * This operation rewrites the vault file using a temporary file to
 * avoid partial data loss in case of failure.
 */

int vault_update(const char *service, const char *username, const char *password) {
    FILE *src = fopen("data/vault.db", "r");
    FILE *tmp = fopen("data/vault.tmp", "w");

    if (src == NULL) {
        printf("Error: could not open vault database\n");
        return 1;
    }

    if (tmp == NULL) {
        printf("Error: could not create temporary file\n");
        fclose(src);
        return 1;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), src) != NULL) {
        if (service_matches(line, service)) {
            fprintf(tmp, "%s|%s|%s\n", service, username, password);
            found++;
            continue;
        }

        fputs(line, tmp);
    }

    fclose(src);
    fclose(tmp);

    if (found) {
        remove("data/vault.db");
        rename("data/vault.tmp", "data/vault.db");
        printf("Service updated successfully\n");
        return 0;
    } else {
        remove("data/vault.tmp");
        printf("Service not found\n");
        return 1;
    }
}