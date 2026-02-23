*This project has been created as part of the 42 curriculum by <mzouhir>, <lmilando>.*

# DESCRIPTION

The goal of this project is to recreate a basic shell, similar to Bash.
By "basic," we mean a shell capable of:
- Displaying a prompt when waiting for a new command.
- Maintaining a working command history.
- Searching for and launching the correct executable (based on the PATH variable or using relative/absolute paths).
- Handling single quotes, double quotes, and redirections (`<`, `>`, `<<`, `>>`).
- Handling pipes (`|`) and environment variable expansion (`$VAR`).
- Retrieving the exit status using the `$?` variable.
- Handling signals: `CTRL-C` displays a new prompt, `CTRL-D` exits the shell, and `CTRL-\` does nothing.
- Implementing the following built-in commands:
    - `echo` with the `-n` option.
    - `cd` with relative or absolute paths only.
    - `pwd` with no options.
    - `export` with no options.
    - `unset` with no options.
    - `env` with no options or arguments.
    - `exit` with no options.

For the bonus part, we also implemented:
- Wildcard management for the current directory (`*`).
- Handling of logical operators `&&` and `||` with parenthesis for command priority.

# INSTRUCTIONS

The instructions for using this project are straightforward:
1. In the root directory, type `make` to compile the program using the Makefile.
2. Use `make clean` to remove object files.
3. Use `make fclean` to remove both object files and the executable.
4. Use `make re` to perform a full recompilation (fclean + all).

Once compiled, launch the program with:
`./minishell`

To quit the program, you can type `exit` or use the `CTRL-D` signal.

# RESOURCES

- [ExplainShell](https://explainshell.com/): Used to learn about shell commands and manual pages.
- [Writing a Unix Shell](https://igupta.in/blog/writing-a-unix-shell-part-3/): Documentation on shell architecture.
- [Write a Shell](https://danishpraka.sh/posts/write-a-shell/): Additional guide on shell implementation.
- [Glibc Manual](https://sourceware.org/glibc/manual/2.42/html_mono/libc.html): Comprehensive C library reference.
- [The Architecture of Open Source Applications (Bash)](https://aosabook.org/en/v1/bash.html): Detailed explanation of how Bash works.
- [Minishell Guide (GibbonTech)](https://www.gibbontech.com/fr/ecole42/minishell/index.html): Great starter guide by a 42 student.
- [CodeQuoi](https://www.codequoi.com/): Amazing resource for 42 projects.
- [Unix Shell (YouTube)](https://www.youtube.com/watch?v=UbhlOk7vjVY): Learning about AST (Abstract Syntax Trees) and shell logic.

AI Usage:
In this project, AI was used as a private tutor. Some concepts were entirely new, and it was sometimes challenging to find specific answers through peer learning alone. After discussing with my peers, I turned to AI to explain complex notions repeatedly and in different ways until I reached the "click" necessary to implement them. Additionally, AI was utilized to refine the grammar, proofread the English text, and ensure the overall clarity of this documentation.
