/*
 * vault.c
 *
 * Implements user-facing vault commands (help/init/etc.).
 *
 * Security boundary:
 * - Command handlers should not print or log sensitive credential material.
 * - Sensitive operations will be centralized in dedicated modules later (crypto/storage).
 */

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
 * Initialize local vault storage (directory + file).
 *
 * Security note: no secrets should be created or stored during init.
 */

void vault_init() {
    printf("init: not implemented yet\n");
}