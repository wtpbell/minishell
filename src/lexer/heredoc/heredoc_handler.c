/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_handler.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 16:39:08 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/23 17:01:55 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Initialise a buffer to temporarily store the input read from the heardoc.
   Create read/write pipes to prepare to pass data. */
static int	init_heredoc_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		ft_putendl_fd("minishell: pipe creation failed", STDERR_FILENO);
		return (0);
	}
	return (1);
}

/* Takes input from readline and checks to see if it matches the delimiter.
   Return 1 if it matches, otherwise 0. */
static int	is_delimiter(char *line, char *delimiter)
{
	if (!line || !delimiter)
		return (0);
	return (ft_strcmp(line, delimiter) == 0);
}

/* Function that writes the contents of a heardoc to a pipe.
   Writes each line to the pipe with a newline character. */
static void	write_to_pipe(int fd, char *content)
{
	write(fd, content, ft_strlen(content));
	write(fd, "\n", 1);
}

/* This is the main processing function of the heardoc.
   Takes in a delimiter, processes the input, and passes it through the pipe. */
int	handle_heredoc(char *delimiter, int *heredoc_fd)
{
	int		pipe_fd[2];
	char	*line;

	if (!init_heredoc_pipe(pipe_fd))
		return (0);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putendl_fd("minishell: warning: here-document ended by EOF",
				STDERR_FILENO);
			break ;
		}
		if (is_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		write_to_pipe(pipe_fd[1], line);
		free(line);
	}
	close(pipe_fd[1]);
	*heredoc_fd = pipe_fd[0];
	return (1);
}
