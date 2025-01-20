/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:13:34 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/20 15:46:57 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>

extern int	g_exit_status;

typedef struct s_cmd
{
	char			**argv;
	char			*infile;
	char			*outfile;
	int				here_doc;
	int				append;
	struct s_cmd	*next;
}	t_cmd;

#endif
