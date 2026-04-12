#ifndef VAULT_H
#define VAULT_H

void vault_banner();
void vault_help();
void vault_init();
void vault_add(int argc, char *argv[]);
void vault_list();
int vault_get(const char *service);
int vault_delete(const char *service);

#endif
