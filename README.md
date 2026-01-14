# minishell 

## 📌 Description
**minishell** is a simplified UNIX shell written in C, developed as part of the **42 School curriculum**.  

## 🛠️ Features

- Display a prompt and wait for user input
- Execute commands with absolute or relative paths
- Built-in commands:
  - `echo` (with `-n`)
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Handle environment variables (`$VAR`)
- Handle exit status (`$?`)
- Redirections:
  - `<` input
  - `>` output
  - `>>` append
  - `<<` heredoc
- Pipes (`|`)
- Signal handling:
  - `Ctrl-C`
  - `Ctrl-D`
  - `Ctrl-\`
    
- `&&` and `||` with  (`()`) for priorities

## ⚙️ Installation
 git clone
 cd minishell
 make
 ./minishell
