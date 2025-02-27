/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 17:54:05 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/27 10:01:47 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*
	echo with -n do not output the trailing newline
	echo with no args, output a newline
	echo with multiple -n, skip those -n
	echo with invalid -n, e.g. -nn, do not output the trailing newline
*/
static int	verify_args(char **args)
{
	int	i;
	int	j;

	if (ft_strcmp(args[1], "-") == 0)
		return (1);
	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		j = 0;
		while (args[i][++j])
		{
			if (args[i][j] != 'n')
				return (i);
		}
		i++;
	}
	return (i);
}

static void	print_escaped_string(const char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (str[i + 1])
			{
				printf("%c", str[i + 1]);
				i += 2;
			}
			else
				printf("%c", str[i++]);
		}
		else
			printf("%c", str[i++]);
	}
}

// int	builtin_echo(t_ast_node *node, t_env **env)
// {
// 	int	i;
// 	int	print_newline;

// 	(void)env;
// 	if (node->argc == 1)
// 		return (printf("\n"), EXIT_SUCCESS);
// 	i = verify_args(node->args);
// 	print_newline = (i == 1);
// 	while (i < node->argc)
// 	{
// 		print_escaped_string(node->args[i]);
// 		if (i + 1 < node->argc)
// 			printf(" ");
// 		i++;
// 	}
// 	if (print_newline)
// 		printf("\n");
// 	return (EXIT_SUCCESS);
// }

int builtin_echo(t_ast_node *node, t_env **env)
{
    int i;
    int print_newline;

    fprintf(stderr, "DEBUG: builtin_echo called with %d args\n", node->argc);
    for (i = 0; i < node->argc; i++) {
        fprintf(stderr, "DEBUG: arg[%d]='%s'\n", i, node->args[i]);
    }

    (void)env;
    if (node->argc == 1)
        return (printf("\n"), EXIT_SUCCESS);
    i = verify_args(node->args);
    print_newline = (i == 1);
    while (i < node->argc)
    {
        fprintf(stderr, "DEBUG: Printing arg[%d]='%s'\n", i, node->args[i]);
        print_escaped_string(node->args[i]);
        if (i + 1 < node->argc)
            printf(" ");
        i++;
    }
    if (print_newline)
        printf("\n");
    return (EXIT_SUCCESS);
}
