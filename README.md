*This project has been created as part of the 42 curriculum by ramarti2 and gregueir.*

# Minishell

## Description

**Minishell** is a simplified Unix shell written in C. The goal of this project is to understand how a real shell works by re-implementing core features such as tokinizing user input, command execution, process management, pipes, redirections, and environment handling.

This project focuses on:

- Understanding how the shell interacts with the operating system  
- Managing processes using `fork`, `execve`, `wait`, and signals  
- Parsing and interpreting user input  
- Reproducing key behaviors of Bash in a minimal but functional shell  

Minishell provides an interactive prompt where users can execute commands, chain them with pipes, redirect input/output, and use built-in commands.

---

## Features

- Interactive prompt
- Command execution with arguments
- PATH resolution
- Environment variable management
- Built-in commands:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Redirections:
  - Input `<`
  - Output `>`
  - Append `>>`
  - Heredoc `<<`
- Pipes (`|`)
- Signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`) similar to Bash
- Proper exit status handling (`$?`)
- Error handling with Bash-like behavior

---

## Project Architecture (High Level)

Our minishell has the following main components:

- **Parser** – Checks for syntax errors (e.g. unclosed quotes, pipes, etc.).
- **Tokenizer** – Breaks user input into tokens (commands, pipes, redirections, etc.) and handles variable expansion.
- **Executor** – Creates processes, sets up pipes and redirections, and runs commands.
- **Built-ins Module** – Handles commands that must run inside the shell process.
- **Signals Module** – Manages signal behavior in interactive and execution modes.
- **Environment Module** – Stores and updates environment variables.

---

## Instructions

### Requirements

- GCC or Clang
- Make  
- Unix-like system (Linux or macOS)

### Compilation

From the root of the repository in bash or zsh, type the following + ENTER:

make

### Execution
Then, run the following command to start minishell:

./minishell

## Resources
- The use of AI was very limited.  Mostly for learning about how shells and project functions work.
  Used very occasionally for help with bug fixing.

- Helpful overview article: https://www.gibbontech.com/ecole42/minishell/index.html

- Another helpful overview by hgamiz-: https://www.notion.so/Minishell-Project-Research-Resources-42-School-23673fe6c2188095beeee6f8e06af9a6?source=copy_link

- Helpful tutorial for pipe() syscall (in spanish): https://youtu.be/l-UhKLdh4aY?si=cA8GoupGACbNKRVu

- Getting help from our peers in person was our most important resource :)

---
Enjoy! :D

Warning: This shell may not be suitable for non-cat lovers :(
