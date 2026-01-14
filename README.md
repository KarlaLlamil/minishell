# minishell 

# 📌 Description
**minishell** is a simplified UNIX shell written in C, developed as part of the **42 School curriculum**.  
This was a team project. I was responsible for defining the internal interfaces and data structures connecting the interpreter to the execution layer, as well as building the interpreter itself. My teammate handled the execution layer.

My work required an in-depth understanding of shell command syntax, including word expansion, token recognition, and grammar production rules. Through this process, I learned a great deal about interpreter design and chose to use an Abstract Syntax Tree (AST) to make execution clearer and more maintainable.

# 🛠️ Features

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

# ⚙️ Installation
- git clone git@github.com:KarlaLlamil/minishell.git
- cd minishell
- make
- ./minishell
