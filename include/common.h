/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   common.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 14:56:46 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/07 10:19:59 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "executor.h"

typedef enum e_mem_context
{
	LEXER,
	PARSER,
	EXECUTOR,
	EXPANDER,
	GENERAL,
	ALL
} t_mem_context;

typedef struct s_mem_tracker
{
	void					*ptr;
	size_t					size;
	struct s_mem_tracker	*next;
}	t_mem_tracker;


void	free_all_memory(void);
void	free_alloc(void *ptr, t_mem_context ctx);
void	free_mem_context(t_mem_context ctx);
void	*mem_alloc(size_t size, t_mem_context ctx);
void	free_tab(char **tab);

/* utils/memory */
t_mem_tracker  *mem_lstnew(void *ptr);
bool	mem_lstclear(t_mem_tracker **lst, void (*del)(void *));
void	mem_lstdelone(t_mem_tracker **head, t_mem_tracker *target);
bool	mem_lstadd_back(t_mem_tracker **lst, t_mem_tracker *new_node);

/*utils/tailor_helper*/
char	*mem_itoa(int n);
char	**mem_split(char const *s, char *set);
char	*mem_strjoin(char const *s1, char const *s2);
char	*mem_strndup(const char *str, int n);
char	*mem_strdup(const char *str);
char	*mem_substr(char const *s, unsigned int start, size_t len);

/*signal*/

void	signals_init(void);
void	interrupt_w_msg(int sig);
void	interrput_slience(int sig);
#endif
