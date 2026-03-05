# c-secure-password-vault

A cybersecurity-focused command-line password vault written in C.

This project is being developed step-by-step to strengthen systems programming skills while exploring secure credential storage concepts. The long-term goal is to build a locally encrypted password vault while learning best practices in secure C development.

---

## Overview

This repository documents the development of a password vault implemented entirely in C.

The project focuses on learning low-level programming concepts while applying them to a security-oriented application. Rather than relying on existing frameworks or libraries for the core architecture, the goal is to understand how systems-level tools are built from the ground up.

As the project evolves, it will incorporate stronger security practices including encryption, secure memory handling, and defensive programming techniques.

---

## Project Goals

This project is designed to strengthen both systems programming and cybersecurity engineering skills.

Key learning goals include:

- designing a modular C codebase using header and implementation separation
- implementing a command-line interface from scratch
- learning secure filesystem practices and permission management
- practicing defensive error handling
- understanding how credential storage systems are designed
- eventually implementing encrypted local storage

---

## Current Features

The project is currently in its early development stage.

Implemented functionality includes:

- basic CLI interface
- `vault help` command
- `vault init` command
- creation of a local vault storage directory
- defensive checks to avoid overwriting existing vault data
- modular C project structure (`src/` and `include/`)

---

## Planned Features

Future development may include:

- encrypted credential storage
- master password authentication
- add / retrieve credential commands
- secure memory handling
- improved file permission enforcement
- automated tests
- additional CLI functionality

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

Display available commands:

``` bash
./vault help
```

Initialize the vault storage:

``` bash
./vault init
```

This creates a local `data/` directory and an empty vault database file.

---

## Security Considerations

This project is intended to explore secure development practices in C.

Current security-focused practices include:

-   restricted directory creation for vault storage
-   defensive checks preventing accidental data overwrites
-   modular code structure to isolate sensitive logic

Future development will focus on:

-   encrypted credential storage
-   secure password handling
-   improved file permission controls
-   safe memory management practices

---

## Development Roadmap

Planned development phases include:

1.  Vault initialization and storage management
2.  Credential storage format
3.  Encryption and secure key handling
4.  Authentication mechanisms
5.  CLI feature expansion
6.  Testing and security improvements

---

## Author

Stephen Ordway  
Computer Science – New Jersey Institute of Technology  
GitHub: https://github.com/FormalProcess3909