#include "builtin.h"

int error_msg(const char *msg, int include_errno)
{
	char *errno_msg;

	write(STDERR_FILENO, "minishell: ", 11);
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	if (include_errno)
	{
		errno_msg = strerror(errno);
		if (errno_msg)
		{
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, errno_msg, ft_strlen(errno_msg));
		}
	}
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

int error_msg_format(const char *prefix, const char *arg, const char *suffix)
{
	if (prefix)
		printf("%s", prefix);
	if (arg)
		printf("%s", arg);
	if (suffix)
		printf("%s", suffix);
	printf("\n");
	return (1);
}
