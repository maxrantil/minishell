# minishell

The minishell project is a program that simulates the behavior of the command shell (also known as the terminal or command prompt) in a Unix-like operating system. When you run the minishell program, it will display a prompt where you can type a command and press enter to execute it. The minishell program is able to parse the command and arguments you enter, and execute the appropriate program. It also has a few built-in functions such as "echo", "cd", "setenv", "unsetenv", "env", and "exit". The minishell program is able to handle expansions (e.g., "$" and "~") and quotes, and has additional features such as the ability to handle relative and absolute paths when using the "cd" command and the ability to print error messages when an error occurs.


## Installation
To install and run minishell, follow these steps:

Clone the repository:
```
git clone https://github.com/maxrantil/minishell.git
```
Navigate to the directory:
```
cd minishell
```
Build the minishell:
```
make
```
Run the minishell:
```
./minishell
```


## About
At Hive Helsinki, a 42 Network school, students must write projects according to the "norme". Many formats are restricted, so the code may look surprising in some places.

Only allowed readymade functions in this project are listed below. Everything
else coded by me, including my own printf, ls-command and c-library(libft).

Allowed readymade functions in this project:

* malloc, free
* access
* open, close, read, write
* opendir, readdir, closedir
* getcwd, chdir
* stat, lstat, fstat
* fork, execve
* wait, waitpid, wait3, wait4
* signal, kill
* exit

Minishell must meet the following requirements:

* Display a prompt and wait for the user to type a command line, which is validated by pressing enter.
* Execute the command and then show the prompt again.
* Support simple commands without pipes, redirections, or other advanced functions.
* Execute external executables located in the directories specified in the ``PATH`` variable.
* Show an error message and display the prompt again if an executable cannot be found.
* Handle errors without using ``errno``, instead displaying a message tailored to the error output.
* Correctly manage the ``PATH`` and the environment (a copy of ``char** environ``).
* Implement a set of built-in commands: ``echo``, ``cd``, ``setenv``, ``unsetenv``, ``env``, and ``exit``.
* 8Support expansions of ``$`` and ``~``.

Additional features:

* Quote handling, including open quotes.
* Custom error message printing.
* ``~`` expansion with ``/ + -`` behind it.
* Full $ expansion support.
* ``cd`` with no directory specified and ``-``, as well as handling relative and absolute paths, ``.`` and ``..``, and errors using ``lstat()``, ``stat()``, and ``access()``.
* ``setenv`` with ``[VAR]=[word]`` and ``unsetenv`` with ``[var]`` arguments.


## Examples
```c
$ cd /home/user/documents   # Change the current working directory to /home/user/documents
$ pwd                       # Print the current working directory
$ setenv VAR value          # Set the environment variable VAR to value
$ echo $VAR                 # Print the value of the environment variable VAR
$ unsetenv VAR              # Unset the environment variable VAR
$ env                       # Print a list of all environment variables
$ exit                      # Exit the minishell
```
