/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anihamba <anihamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:06:19 by anihamba          #+#    #+#             */
/*   Updated: 2025/04/16 11:01:46 by ani              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*str_buff;
	struct s_list	*next;
}			t_list;

char	*get_next_line(int fd);
char	*get_the_line(t_list *list);
t_list	*find_last_node(t_list *list);
int		has_new_line(t_list *list);
int		length_of_new_line(t_list *list);
void	str_copy(t_list *list, char *str);
void	free_the_list(t_list **list, t_list *clean_node, char *buf);
void	append(t_list **list, char *buf);
void	polish_the_list(t_list **list);
void	create_list(t_list **list, int fd);

#endif
