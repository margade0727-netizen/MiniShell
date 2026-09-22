# MiniShell

MiniShell is a small Windows command-line shell written in C. It is a learning
project for command dispatch, Win32 filesystem APIs, input parsing, and clear
error handling. Built-in commands are found through a command table; they are
not forwarded to `cmd.exe`.

## Build and run

Requires a Windows C compiler with Win32 headers, such as MinGW GCC.

```powershell
gcc -Wall -Wextra -Werror main.c functions.c -o minishell.exe
.\minishell.exe
```

Type `help` after starting the shell. Use `exit` or `quit` to close it.

## Implemented commands

| Command | Aliases | Purpose |
| --- | --- | --- |
| `whereami` | — | Print the current working directory. |
| `whoami` | — | Print the current Windows user. |
| `cd path` | — | Change the current working directory. |
| `list` | `ls` | List files and folders in the current directory. |
| `create name` | `crt` | Create an empty file; `.txt` is added when no extension is supplied. |
| `rename old new` | `rnm` | Rename a file or folder. |
| `move source|destination` | `mv` | Move an item without overwriting an existing destination. |
| `del path` | `rem` | Delete a file. |
| `deldir path` | `rmdir` | Delete an empty directory. |
| `open path` | `op` | Print a text file's contents. |
| `open2 [editor|]path` | `op2` | Open a file with a CLI editor found on `PATH`. |
| `echo text` | — | Print text. |
| `help` | — | Show the command list. |
| `help-error [code]` | — | Explain one three-digit error code, or list all codes. |

Run `help` for the full catalogue.

## Error codes

Run `help-error` for the catalogue.

## Current limitations

- Windows only; the project uses Win32 and Microsoft C runtime APIs.
- Arguments are currently one plain text string. Quoted paths and paths with
  spaces are not supported reliably by multi-path commands.
- No command history, tab completion, pipes, redirection, wildcards, or
  recursive deletion.
- `open` is intended for text files and truncates content larger than its
  fixed buffer.
- `open2` does not install software automatically; install a supported editor
  (micro, nano, edit, or vim) yourself. //Used to try to install it

## Documentation

- [User guide](Documentation.md)
- [Developer guide](Documentation2.md)
- [Implementation ideas](suggestion.md)
- Got too lazy and wrote sh1t documentation so didn't push it. Gonna improve it and push it when I stop feeling lazy.
## Status

Abandoned! -> I have an interest to make a GUI version of it as I have an unexplainable hatred for windows explorer. Will try it when I get a change, and it was a nice few hours to do this.
