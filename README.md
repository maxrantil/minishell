# minishell

42 project, recoding our own little bash. A program capable of parsing a prompt and launching executables with arguments, along with a few built-in functions.

# How to use it

Using ``make`` will create the minishell executable.

And then,
simply run it with :
```
./minishell
```

Only allowed readymade functions in this project are listed below. Everything
else coded by me, including my own printf, ls-command and c-library.

Allowed readymade functions in this project:

    - malloc, free
    - access
    - open, close, read, write
    - opendir, readdir, closedir
    - getcwd, chdir
    - stat, lstat, fstat
    - fork, execve
    - wait, waitpid, wait3, wait4
    - signal, kill
    - exit

Mandatory requirements of the project:

    - You must program a miniUNIXcommand interpreter.
    - This interpreter must display a prompt (a simple "$>" for example) and
    wait tillyou type a command line, validated by pressing enter.
    - The prompt is shown again only once the command has been completely
    executed.
    - The command lines are simple, no pipes, no redirections or any other
    advanced functions.
    - The executable are those you can find in the paths indicated in the
    PATH variable.
    - In cases where the executable cannot be found, it has to show an error
    message anddisplay the prompt again.
    - You must manage the errors without using errno, by displaying a message
    adaptedto the error output.
    - You must deal correctly with the PATH and the environment (copy of
    systemchar**environ).
    - You must implement a series of builtins: echo,cd,setenv,unsetenv,env,exit.
    - You can choose as a reference whatever shell you prefer.
    - You must manage expansions $ and ̃

Additional features:

    - Handling of quotes, also if quote is left open
    - Error message printing
    
Add on features:

    - ~ (tilde) with / + - behind it
    - $ expansion working
    - cd [dir] also works with no dir and - Handles relative and absolute paths.
    Checks the path for any errors, error handling written by hand with lstat(),
    stat() and access(). Handles . and ..
    - setenv [VAR] [word]
    - unsetenv [var]
    - all error are handled manually and error messages printed to the fd2
