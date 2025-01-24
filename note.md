1. Command-Line Input and History Management

a. readline:
Reads a single line of input from the user, displaying a prompt.
It handles input interactively, supports editing (e.g., arrow keys),
and offers a polished experience for the user.

b. add_history:
Adds the provided input line to the history buffer so the user can recall 
it using the up/down arrow keys in future sessions.

c. rl_clear_history: 
Clears all history entries. Use this to manage memory 
or reset history when exiting the shell.

d. rl_on_new_line, rl_replace_line, rl_redisplay: 
Functions for customizing the line-editing behavior of readline.
e.g.	rl_on_new_line();              // Notify readline about a new line
		rl_replace_line("new input", 1); // Replace the current input line
		rl_redisplay();                // Redisplay the updated line

2. Signal Handling

a. signal: 
Installs a signal handler for a specific signal.
e.g. signal(SIGINT, handle_sigint); // Handle Ctrl+C

b. sigaction:
A more robust alternative to signal for handling signals.

c. kill: Sends a signal to a process.
e.g. kill(pid, SIGKILL); // Forcefully kill a process

3. File and Directory Management

a. stat, lstat, fstat: Get information about a file.
e.g. struct stat file_stat;
	if (stat("file.txt", &file_stat) == 0) 
		printf("File size: %ld bytes\n", file_stat.st_size);
struct stat {
	dev_t st_dev; ID of device containing the file.
	ino_t st_ino; Serial number for the file.
	mode_t st_mode; Access mode and file type for the file (see Flags).
	nlink_t st_nlink; Number of links to the file.
	uid_t st_uid; User ID of file owner.
	gid_t st_gid; Group ID of group owner.
	dev_t st_rdev; Device ID (if the file is a character or block special device).
	off_t st_size; File size in bytes (if the file is a regular file).
	time_t st_atime; Time of last access.
	time_t st_mtime; Time of last data modification.
	time_t st_ctime; Time of last file status change.
	blksize_t st_blksize; A file system-specific preferred I/O block size for this object. 
						On some file system types, this may vary from file to file.
	blkcnt_t st_blocks; Number of blocks allocated for this file.
	mode_t st_attr; The DOS-style attributes for this file (see Flags). 
					This is a PTC MKS Toolkit UNIX APIs extension.
}; 

b. getcwd: Gets the current working directory.
e.g. char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)))
	printf("Current directory: %s\n", cwd);

c. chdir: Changes the current working directory.
e.g. chdir("/home/user");

d.unlink: Deletes a file.
e.g.unlink("file.txt");

3. Directory Navigation
- opendir, readdir, closedir: Functions for reading directories.
e.g. DIR *dir = opendir(".");
	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL)
	{
	printf("%s\n", entry->d_name);
	}
	closedir(dir);

4. TTY and Terminal Control

a. isatty: Checks if a file descriptor is associated with a terminal.
e.g. if (isatty(STDIN_FILENO))
		printf("Interactive shell\n");

b. ttyname: Gets the name of the terminal associated with a file descriptor.
e.g. printf("Terminal: %s\n", ttyname(STDIN_FILENO));

c. ioctl: Configures device settings. Commonly used for terminals.

d. tcsetattr, tcgetattr: Set or get terminal attributes.
