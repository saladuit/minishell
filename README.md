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

| Function		| Manual Page		| From lib			| Description
| :--			| :--				| :--				| :--
| **printf**	| `man 3 printf`	| `<stdio.h>`		| write output to stdout
| **malloc**	| `man malloc`		| `<stdlib.h>`		| allocate dynamic memory
| **free**		| `man 3 free`		| `<stdlib.h>`		| free dynamic memory
| **read**		| `man 2 read`		| `<unistd.h>`		| read from a file descriptor
| **write**		| `man 2 write`		| `<unistd.h>`		| write to a file descriptor
| **open**		| `man 2 open`		| `<fcntl.h>`		| open and possibly create a file
| **close**		| `man 2 open`		| `<unistd.h>`		| close a file descriptor
| **fork**		| `man fork`		| `<unistd.h>`		| create a child process
| **wait**		| `man wait`		| `<sys/wait.h>`	| wait for process to change state
| **waitpid**	| `man waitpid`		| `<sys/wait.h>`	| wait for process to change state
| **wait3**		| `man wait3`		| `<sys/wait.h>`	| (obsolete) wait for process to change state, BSD style
| **wait4**		| `man wait4`		| `<sys/wait.h>`	| (obsolete) wait for process to change state, BSD style
| **signal**	| `man signal`		| `<signal.h>`		| ANSI C signal handling
| **kill**		| `man 2 kill`		| `<signal.h>`		| send signal to a process
| **exit**		| `man exit`		| `<stdlib.h>`		| cause normal process termination
| **getcwd**	| `man getcwd`		| `<unistd.h>`		| get current working directory
| **chdir**		| `man chdir`		| `<unistd.h>`		| change working directory
| **stat**		| `man 2 stat`		| `<sys/stat.h>`	| get file status by pathname
| **lstat**		| `man lstat`		| `<sys/stat.h>`	| get file status by pathname (for symlinks)
| **fstat**		| `man fstat`		| `<sys/stat.h>`	| get file status by fd
| **execve**	| `man execve`		| `<unistd.h>`		| execute program
| **dup**		| `man dup`			| `<unistd.h>`		| duplicate a file descriptor
| **dup2**		| `man dup2`		| `<unistd.h>`		| duplicate a file descriptor
| **pipe**		| `man pipe`		| `<unistd.h>`		| create pipe
| **opendir**	| `man opendir`		| `<dirent.h>`		| open a directory
| **readdir**	| `man readdir`		| `<dirent.h>`		| read a directory
| **closedir**	| `man closedir`	| `<dirent.h>`		| close a directory
| **strerror**	| `man strerror`	| `<string.h>`		| return string describing error number
| **errno**		| `man errno`		| `<errno.h>`		| number of last error
| **termcap**	| `man termcap`, `man termios`		| `<term.h>`		| direct curses interface to the terminfo capability database
