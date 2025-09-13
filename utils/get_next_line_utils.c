/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anihamba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:06:49 by anihamba          #+#    #+#             */
/*   Updated: 2025/09/13 13:17:05 by anihamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

t_list	*find_last_node(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	has_new_line(t_list *list)
{
	int	i;

	i = 0;
	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->str_buff[i] && i < BUFFER_SIZE)
		{
			if (list->str_buff[i] == '\n')
				return (1);
			++i;
		}
		list = list->next;
	}
	return (0);
}

int	length_of_new_line(t_list *list)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->str_buff[i])
		{
			if (list->str_buff[i] == '\n')
			{
				++len;
				return (len);
			}
			++len;
			++i;
		}
		list = list->next;
	}
	return (len);
}

void	str_copy(t_list *list, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!list)
		return ;
	while (list)
	{
		i = 0;
		while (list->str_buff[i])
		{
			if (list->str_buff[i] == '\n')
			{
				str[j++] = '\n';
				str[j] = '\0';
				return ;
			}
			str[j++] = list->str_buff[i++];
		}
		list = list->next;
	}
	str[j] = '\0';
}

void	free_the_list(t_list **list, t_list *clean_node, char *buf)
{
	t_list	*temp;

	if (!*list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->str_buff);
		free(*list);
		*list = temp;
	}
	*list = NULL;
	if (clean_node && clean_node->str_buff && clean_node->str_buff[0])
		*list = clean_node;
	else
	{
		free(clean_node);
		free(buf);
	}
}
