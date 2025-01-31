# Command-Line Input and History Management

## a. readline:
Reads a single line of input from the user, displaying a prompt. It handles input interactively, supports editing (e.g., arrow keys), and offers a polished experience for the user.

## b. add_history:
Adds the provided input line to the history buffer so the user can recall it using the up/down arrow keys in future sessions.

## c. rl_clear_history: 
Clears all history entries. Use this to manage memory or reset history when exiting the shell.

## d. rl_on_new_line, rl_replace_line, rl_redisplay:
Functions for customizing the line-editing behavior of readline.

```c
rl_on_new_line();              // Notify readline about a new line
rl_replace_line("new input", 1); // Replace the current input line
rl_redisplay();                // Redisplay the updated line
```

# Signal Handling

## a. signal:
Installs a signal handler for a specific signal.

```c
signal(SIGINT, handle_sigint); // Handle Ctrl+C
```

## b. sigaction:
A more robust alternative to signal for handling signals.

## c. kill:
Sends a signal to a process.

```c
kill(pid, SIGKILL); // Forcefully kill a process
```

# File and Directory Management

## a. stat, lstat, fstat:
Get information about a file.

```c
struct stat file_stat;
if (stat("file.txt", &file_stat) == 0) 
    printf("File size: %ld bytes\n", file_stat.st_size);
```

### struct stat:
```c
struct stat {
    dev_t     st_dev;     // Device ID of the filesystem
    ino_t     st_ino;     // Inode number
    mode_t    st_mode;    // File type and mode (permissions)
    nlink_t   st_nlink;   // Number of hard links
    uid_t     st_uid;     // User ID of the owner
    gid_t     st_gid;     // Group ID of the owner
    off_t     st_size;    // File size in bytes
    time_t    st_atime;   // Time of last access
    time_t    st_mtime;   // Time of last modification
    time_t    st_ctime;   // Time of last status change
    blksize_t st_blksize; // Preferred I/O block size
    blkcnt_t  st_blocks;  // Number of blocks allocated
    mode_t    st_attr;    // DOS-style attributes (MKS Toolkit extension)
};
```

## b. getcwd:
Gets the current working directory.

```c
char cwd[1024];
if (getcwd(cwd, sizeof(cwd)))
    printf("Current directory: %s\n", cwd);
```

## c. chdir:
Changes the current working directory.

```c
chdir("/home/user");
```

## d. unlink:
Deletes a file.

```c
unlink("file.txt");
```

# Directory Navigation

## opendir, readdir, closedir:
Functions for reading directories.

```c
DIR *dir = opendir(".");
struct dirent *entry;
while ((entry = readdir(dir)) != NULL) {
    printf("%s\n", entry->d_name);
}
closedir(dir);
```

# TTY and Terminal Control

## a. isatty:
Checks if a file descriptor is associated with a terminal.

```c
if (isatty(STDIN_FILENO))
    printf("Interactive shell\n");
```

## b. ttyname:
Gets the name of the terminal associated with a file descriptor.

```c
printf("Terminal: %s\n", ttyname(STDIN_FILENO));
```

## c. ioctl:
Configures device settings. Commonly used for terminals.

## d. tcsetattr, tcgetattr:
Set or get terminal attributes.

# Command Categories

| Command   | Scope                  | Hidden | Execution Context |
|-----------|------------------------|--------|-------------------|
| cd        | Local + Environment    | No     | Parent            |
| export    | Environment (Exported) | No     | Parent            |
| unset     | Environment/Local      | Yes    | Parent            |
| exit      | Local                  | No     | Parent            |
| echo      | Local                  | No     | Child             |
| env       | Environment (Exported) | No     | Child             |
| pwd       | Local                  | No     | Child             |
| ls        | Local                  | No     | Child             |
| grep      | Local                  | No     | Child             |
| history   | Local                  | No     | Parent            |
| kill      | Local                  | No     | Child             |
| type      | Local                  | No     | Parent            |

# Scope Example

| Command       | Scopes                     | Example                                                |
|---------------|----------------------------|--------------------------------------------------------|
| export VAR=1  | Environment (Both)         | Variable VAR is available to both parent and children. |
| unset VAR     | Local/Environment Hidden   | Variable VAR is hidden in the parent and not passed.   |

# Execution Context Summary

| Context  | Commands                                                             |
|----------|----------------------------------------------------------------------|
| Parent   | cd, export, unset, history                                           |
| Child    | ls, grep, pwd, env, echo, kill, test, which                          |
| Both     | None                                                                 |

# Key Notes

- **Parent Process (Expansion):**
  - The shell performs expansions such as:
    - **Variable expansion:** Replace `$HOME` with `/home/user`.
    - **Wildcard expansion:** Replace `*.txt` with `file1.txt file2.txt`.
    - **Command substitution:** Replace `$(pwd)` with the output of `pwd`.
  - The resulting expanded command is passed to the child process for execution.

- **Child Process (Execution):**
  - The shell forks a new process to execute the expanded command, preserving the parent shell state.


# Buildin commands

- **Export Command:**
  -**Marks Variables for Export:** export does not create new variables. Instead, it marks existing shell variables as environment variables, making them available to child processes.
  -**Updates the Environment:** once a variable is exported, it is added to the shell's environment list, which is inherited by all subsequent child processes.
  - **Persistent for the Session:** exported variables remain in the shell's environment until explicitly removed (e.g., with unset) or until the shell session ends.

- **Command Syntax**
export VAR=value				# Define and export a variable in one step.
								Any child processes will now inherit VAR
VAR=value; export VAR			# create local variable, then mark an existing variable for export
export VAR1 VAR2				# Mark multiple variables for export
export -p						# List all exported variables
unset VAR						# Remove VAR entirely(both local variables and environment)


# getcwd fail

  -**pwd Command Behaviour:** pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
  -**execvp() Command Behaviour:** e.g. ls: cannot open directory '.': No such file or directory

