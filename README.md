# minishell
[![Coverage Status](https://coveralls.io/repos/github/saladuit/minishell/badge.svg)](https://coveralls.io/github/saladuit/minishell) [![unit](https://github.com/saladuit/minishell/actions/workflows/c.yml/badge.svg)](https://github.com/saladuit/minishell/actions/workflows/c.yml)

## Description

This project is about creating a simple shell. 
Yes, our own little bash. We will learn a lot about processes and file descriptors.

## Features
- A custom shell interpreter similar to bash and zsh, called minishell
- Support for  built-in shell commands echo, cd, pwd, export, unset, env and exit
- Full support for PATH resolution and the execve system call to run external commands
- Advanced command line editing using the readline library, including support for history
- Advanced error handling and reporting, with informative error messages and exit codes
- Support for input/output redirection and pipes
- Environment variable expansion and substitution using the $ symbol
- Advanced signal handling, including support for Ctrl+C and Ctrl+\ signals
- Comprehensive unit tests and system tests to ensure robustness and correctness
- Advanced debugging tools, including support for valgrind and fsanitize for memory leak detection and error reporting
- Convenient and intuitive Makefile commands for easy compilation, testing, and debugging of the project

## Contributing
1. Clone the repo
```
git clone https://github.com/saladuit/minishell.git
```
2. Create a new branch (`git checkout -b my_branch`)
3. Make changes and test them
4. Push to the branch (`git push origin my_branch`)
5. Create a pull request to push to main
6. Review

### Executing program
```
./minishell.out
```

## Makefile Commands
### Compilation
- `make`: Compiles the project
- `make debug`: Compiles the project with debug flags
- `make fsan`: Compiles the project with debug flags and fsanitize=undefined
- `make valgrind`: Runs the project with valgrind to detect memory leaks
### Testing
- `make test`: Runs all unit tests and system tests
- `make test FILTER='<test_filter>'`: test a specific module within the system
- `make test FILTER='minishell/export*'`: test the whole sytem and only the export cases
- `make test FILTER='lexer/*'`: test a module and run all cases
- `make ftest`: Same as make test but also compiles with fsanitize=undefined
- `make ftest FILTER='<test_filter>'`: test a specific module within the system
- `make ftest FILTER='minishell/export*'`: test the whole sytem and only the export cases
- `make ftest FILTER='lexer/*'`: test a module and run all cases
### Re-compilation
- `make re`: Same as make fclean and make
- `make test_re`: Same as make test but also removes all object files and executables
- `make ftest_re`: Same as make ftest but also removes all object files and executables
### Coverage
- `make coverage`: Runs gcov on all source files and generates a coverage report
- `make analyse`: Generates a coverage report and opens it up
### Cleaning
- `make clean`: Removes all object files
- `make fclean`: Removes all object files and executables
- `make covclean`: Removes all coverage-related files and calls fclean

## Test-Driven Development (TDD)
It is recommended to use Test-Driven Development as the main development cycle. 
This means that you should write a test for the code you are going to write before you write it. 
This helps ensure that your code behaves as expected and that you catch any bugs early in the development cycle.

When writing tests, please follow these naming conventions:
1. The function with the assertion should be named `assert_<function_name>`.
2. The test macro should be defined like so: `Test(<function_name>, <descriptive_case_name>)`.
3. The test case itself should have preferably only one function call to the assertion function.
4. Keep the test cases concise, descriptive and simple.

## Continuous Integration
We use GitHub Actions to automatically run tests on every push to the main branch. 
The `c.yml` YAML file defines the build and test jobs that are run. 
Specifically, it installs necessary dependencies, builds the project, runs tests, generates coverage reports, 
and uploads the reports to Coveralls for code coverage analysis.

It is important to have this in place because it allows us to catch any potential errors or 
issues with the codebase early on in the development process. 
This helps to ensure that the codebase remains stable and functional. 
Additionally, it provides visibility into the code coverage of the project, 
which can help us identify areas that need more testing.

If you make changes to the codebase, 
please ensure that the build and tests pass before pushing your changes to the main branch.

#### Useful Sources
- [Readline guide](https://web.mit.edu/gnu/doc/html/rlman_2.html)
- [GNU Bash Manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual)
- [Readline Manual](https://man7.org/linux/man-pages/man3/readline.3.html)
- [Terminal Interface](https://www.gnu.org/software/libc/manual/html_node/Low_002dLevel-Terminal-Interface.html)
