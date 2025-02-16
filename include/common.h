/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   common.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 14:56:46 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/16 14:01:20 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "executor.h"

typedef struct s_mem_tracker
{
	void					*ptr;
	size_t					size;
	struct s_mem_tracker	*next;
}	t_mem_tracker;


void	free_all_memory(void);
void	free_alloc(void *ptr);
void	free_mem_context(void);
void	*mem_alloc(size_t size);
void	free_tab(char **tab);
void	free_env(t_env **env);

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
void	interrput_silence(int sig);
#endif
