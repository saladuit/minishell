# minishell
This project is about creating a simple shell. Yes, our own little bash. We will learn a lot about processes and file descriptors.

## Description

## Getting Started

### Installing
```
git clone https://github.com/saladuit/Philosophers.git
cd minishell
make
```

### Executing program

```
./minishell
```
### Rules
- Display a prompt when waiting for a new command.
- Have a working history.
- Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
- Not use more than one global variable. Think about it. You will have to explain its purpose.
- Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
- Handle ’ (single quote) which should prevent the shell from interpreting the meta- characters in the quoted sequence.
- Handle " (double quote) which should prevent the shell from interpreting the meta- characters in the quoted sequence except for $ (dollar sign).
- Implement redirections:
  - < should redirect input.
  - > should redirect output.
  - << should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
  - >> should redirect output in append mode.
- Implement pipes (| character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.
- Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
- Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
- Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
- In interactive mode:
  - ctrl-C displays a new prompt on a new line. ◦ ctrl-D exits the shell.
  - ctrl-\ does nothing.
- Your shell must implement the following builtins:
  - echo with option -n
  - cd with only a relative or absolute path ◦ pwd with no options
  - export with no options
  - unset with no options
  - env with no options or arguments
  - exit with no options
 
### Functions allowed in this project

| Function		| Description
| :--			| :--
| **readline**	| get a line from a user with editing
| **rl_clear_history**	| free readline history
| **rl_on_new_line**	| write output to stdout
| **rl_replace_line**	| replaces line with new content
| **rl_redisplay**	| redisplays line
| **add_history**	| Add user input to history
| **printf**	| write output to stdout
| **malloc**	| allocate dynamic memory
| **free**		| free dynamic memory
| **write**		| write to a file descriptor
| **access**		| check accessibility of a file
| **open**		| open and possibly create a file
| **read**		| read from a file descriptor
| **close**		| close a file descriptor
| **fork**		| create a child process
| **wait**		| wait for process to change state
| **waitpid**	| wait for process to change state
| **wait3**		| (deprecated) wait for process to change state, BSD style
| **wait4**		| (deprecated) wait for process to change state, BSD style
| **signal**	| ANSI C signal handling
| **sigaction**	| ANSI C signal handling
| **kill**		| send signal to a process
| **exit**		| cause normal process termination
| **getcwd**	| get current working directory
| **chdir**		| change working directory
| **stat**		| get file status by pathname
| **lstat**		| get file status by pathname (for symlinks)
| **fstat**		| get file status by fd
| **execve**	| execute program
| **dup**	    | duplicate a file descriptor
| **dup2**		| duplicate a file descriptor
| **pipe**		| create pipe
| **opendir**	| open a directory
| **readdir**	| read a directory
| **closedir**	| close a directory
| **strerror**	| return string describing error number
| **errno**		| number of last error
| **termcap**	| direct curses interface to the terminfo capability database

#### Useful Sources
- [Readline guide](https://web.mit.edu/gnu/doc/html/rlman_2.html)
- [GNU Bash Manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual)
- [Readline Manual](https://man7.org/linux/man-pages/man3/readline.3.html)
- [Terminal Interface](https://www.gnu.org/software/libc/manual/html_node/Low_002dLevel-Terminal-Interface.html)
