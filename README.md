# c-secure-password-vault

A cybersecurity-focused command-line password vault written in C.

This project is developed step-by-step to strengthen systems programming skills while exploring secure credential storage concepts. The long-term goal is to build a locally encrypted password vault while applying best practices in secure C development.

---

## Overview

This repository documents the development of a password vault implemented entirely in C.

The project focuses on learning low-level programming concepts while applying them to a security-oriented application. Rather than relying on external frameworks, the goal is to understand how systems-level tools are built from the ground up.

As the project evolves, it will incorporate stronger security practices including encryption, secure memory handling, and defensive programming techniques.

---

## Project Goals

This project is designed to strengthen both systems programming and cybersecurity engineering skills.

Key learning goals include:

- designing a modular C codebase using header and implementation separation
- implementing a command-line interface from scratch
- applying secure filesystem practices and permission management
- practicing defensive error handling
- understanding how credential storage systems are designed
- implementing encrypted local storage (planned)

---

## Current Features

The project currently implements a complete set of core vault operations for managing credentials.

Implemented functionality includes:

- basic CLI interface with command routing
- `vault help` command for usage information
- `vault init` command to initialize secure vault storage
- `vault add <service> <username> <password>` to store credentials (enforces unique service names)
- `vault list` to display all stored credentials
- `vault get <service>` to retrieve credentials for a specific service
- `vault delete <service>` to remove credentials for a service
- `vault update <service> <username> <password>` to update credentials for a service
- file-based credential storage using a structured format (`service|username|password`)
- safe file rewrite patterns for update and delete operations
- defensive checks to prevent accidental data overwrites
- modular C project structure (`src/` and `include/`)

### Design Decisions

- each service name must be unique within the vault
- duplicate entries are rejected at insertion time
- update and delete operations operate on entire service entries
- vault data is currently stored in plaintext (to be secured in future phases)

---

## Planned Features

Future development will focus on transforming the vault into a secure credential storage system.

### Phase 2 — Security Enhancements

- encrypted credential storage
- master password authentication
- secure handling of sensitive data in memory
- restricted visibility of stored credentials (avoid printing plaintext by default)
- improved file permission enforcement

### Phase 3 — Engineering Improvements

- automated tests for CLI functionality
- improved input validation and error handling
- enhanced modular design (separating storage and security logic)
- additional CLI functionality (search, export, etc.)

---

## Project Structure
```
.
├── src/        # C source files
├── include/    # header files
├── data/       # vault storage (ignored by git)
├── Makefile    # build automation
└── README.md
```

## Building the Project

Compile the project using:

``` bash
make
```

Clean build artifacts:

``` bash
make clean
```

------------------------------------------------------------------------

## Usage

### Available Commands

- `vault help` — display usage information  
- `vault init` — initialize vault storage  
- `vault add <service> <username> <password>` — store credentials  (unique service required) 
- `vault list` — list all stored credentials  
- `vault get <service>` — retrieve credentials for a service
- `vault delete <service>` — remove credentials for a service
- `vault update <service> <username> <password>` — update credentials for a service

### Examples

Display available commands:

``` bash
./vault help
```

Initialize the vault storage:

``` bash
./vault init
```

This creates a local `data/` directory and an empty vault database file.

Add a credential:

```bash
./vault add github john mypassword
```

List stored credentials:

```bash
./vault list
```

Example output:
```text
github|john|mypassword
```

Retrieve a credential:

```bash
./vault get github
```

Example output:
```text
github|john|mypassword
```

Delete a credential:

```bash
./vault delete github
```

Example output:
```text
Service deleted successfully
```

Update a credential:

```bash
./vault update github user newpassword
```

Example output:
```text
Service updated successfully
```

---

## Security Considerations

This project is designed to explore secure development practices in C.  

At the current stage (Phase 1), credentials are stored in plaintext and are not protected against unauthorized access. This is an intentional design choice to focus on building core functionality before introducing security mechanisms.

### Current Practices

- restricted directory creation for vault storage (`0700` permissions)
- defensive checks preventing accidental data overwrites
- safe file rewrite patterns for update and delete operations
- modular code structure to isolate credential handling logic

### Known Limitations

- credentials are stored in plaintext
- credentials are displayed directly via CLI commands
- no authentication mechanism is required to access the vault
- no encryption or key management is implemented

### Future Improvements (Phase 2)

- master password authentication
- encrypted credential storage
- secure in-memory handling of sensitive data
- restricted visibility of credentials in CLI output
- improved file permission enforcement

---

## Development Roadmap

### Phase 1 — Core Vault Functionality (Completed)

- CLI command routing and structure
- vault initialization and storage management
- credential storage format (`service|username|password`)
- core operations:
  - add
  - list
  - get
  - delete
  - update
- duplicate prevention (unique service names)
- safe file rewrite patterns for update and delete

### Phase 2 — Security Enhancements (In Progress)

- master password authentication
- encrypted credential storage
- secure handling of sensitive data in memory
- restricted visibility of credentials in CLI output
- improved file permission enforcement

### Phase 3 — Engineering & Usability Improvements

- automated testing framework (`tests/`)
- improved input validation and error handling
- modular separation of storage and security components
- additional CLI features (search, export, etc.)

---

## Author

Stephen Ordway  
Computer Science – New Jersey Institute of Technology  
GitHub: https://github.com/FormalProcess3909