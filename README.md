# Bash Implementation Project

This project aims to implement a basic version of a Bash shell, which supports various functionalities. Here's a comprehensive breakdown of the project's features and requirements:

This project was collaboratively created with [Arai](https://github.com/MasaDevs/). I would like to express my deepest gratitude to Arai for their invaluable contributions and support.

## General Features

- **Prompt Display**: The shell should display a prompt whenever it's waiting for a new command.
  
- **History Management**: It should maintain a history of commands entered by the user.

- **Command Execution**: Search and launch the right executable based on the PATH variable or using relative or absolute paths.
  
- **Global Variable**: Use no more than one global variable. 

- **Quote Handling**: 
  - Handle `'` (single quote): Prevents the shell from interpreting the meta-characters within the quoted sequence.
  - Handle `"` (double quote): Prevents the shell from interpreting the meta-characters within the quoted sequence except for `$` (dollar sign).

- **Special Characters**: Do not interpret unclosed quotes or characters that aren't required for this project, such as `\` (backslash) or `;` (semicolon).

## Redirections & Pipelines

- **Redirections**:
  - `<`: Redirect input.
  - `>`: Redirect output.
  - `<<`: Accept a delimiter and read input until a line containing the delimiter appears. It should not update the command history.
  - `>>`: Redirect output in append mode.

- **Pipes**: Implement pipes (`|` character). The output of each command in the pipeline should be connected to the input of the subsequent command through a pipe.

## Variables & Controls

- **Environment Variables**: Handle `$` followed by a sequence of characters, which should expand to their values.

- **Exit Status**: Handle `$?` which should represent the exit status of the most recently executed foreground pipeline.

- **Control Keys**:
  - `ctrl-C`: In interactive mode, display a new prompt on a new line.
  - `ctrl-D`: Exit the shell.
  - `ctrl-\`: Do nothing.

## Built-in Commands

Your shell should implement the following builtins:

- `echo` with the `-n` option.
- `cd`: Navigate using only a relative or absolute path.
- `pwd`: Display the current directory without any options.
- `export`: Set environment variables without options.
- `unset`: Remove variables without options.
- `env`: Display environment variables without options or arguments.
- `exit`: Exit the shell without options.

---
