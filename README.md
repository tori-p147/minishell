# Minishell

*This project has been created as part
of the 42 curriculum by [vmatsuda](https://github.com/tori-p147) and [ssugaya](https://github.com/ssugaya-42)*

## Description

### Goal of Minishell
  Create a custom version of a command-line shell with support for handling pipes and redirections. 
Additionally, to implement the built-in commands independently: echo, cd, pwd, export, unset, env, and exit.

## Instructions
  The project requires the following:

- C compiler such as gcc
- Unix-like operating system

No additional libraries or dependencies are needed.

## Project Structure
```
minishell/
├── src/
│   ├── tokenizer/
│   ├── parser/
│   ├── executor/
│   └── utils/
│   └── errors/
├── includes/
├── libs/
├── Makefile
└── README.md
```

## Architecture Overview

  The core logic of the program is organized into three main layers: **tokenizer**, **parser**, and **executor**.

  The **tokenizer** processes the user input string and splits it into an array of tokens.
It also performs environment variable expansion when needed.

  The **parser** transforms the array of tokens into a list of commands.
Each command contains a list of redirections, which are later handled appropriately by the executor.

  The **executor** receives the structured commands and executes them, applying pipes and redirections as defined.

## Resources
1. [Bash Documentation](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html)
2. [Understanding Piping and Redirection in Bash](https://www.youtube.com/watch?v=H9MLzwVJwsQ)

