_This project has been created as part of the 42 curriculum by weizhang and fdong._

# Minishell

## Description

Minishell is a simple shell written in C. It is a subset of `bash --posix`.

### Features

- Display a prompt and maintain a working history
- Search and launch executables based on `PATH` or relative/absolute paths
- Handle single quotes `'` and double quotes `"`
- Redirections: `<`, `>`, `>>`, `<<` (heredoc)
- Pipes `|`
- Environment variable expansion (`$VAR`, `$?`)
- Signal handling: `ctrl-C`, `ctrl-D`, `ctrl-\` behave like in bash
- Logical operators `&&`, `||` with parentheses for priorities
- Built-in commands: `echo -n`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

## Instructions

### Build

```bash
make        # Build the minishell executable
make bonus  # Build the minishell executable
make clean  # Remove object files
make fclean # Remove object files and the executable
make re     # Rebuild from scratch
```

### Run

```bash
./minishell
```

### Test

```bash
make test
```

### Valgrind

```bash
valgrind --suppressions=readline.supp --show-leak-kinds=all --leak-check=full ./minishell
```

## Resources

- [Pratt parsing](https://www.youtube.com/watch?v=0c8b7YfsBKs&t=1046s)
- [minishell_tester](https://github.com/LucasKuworwornu/minishell_tester)

## AI Usage

AI tools were used during this project for the following purposes:

- **Code review** -- checking for bugs, edge cases, and norm compliance
- **Design discussions** -- discussing architecture choices (e.g. Pratt parsing vs recursive descent, AST design)
- **Writing the README** -- drafting and formatting this document
- **Understanding system calls** -- getting explanations for `fork`, `execve`, `pipe`, `dup2`, `waitpid`, `sigaction`, etc.

All code was written and understood by the team. AI was not used to generate shell logic or implementation code.
