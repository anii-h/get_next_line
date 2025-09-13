/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anihamba <anihamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:51:49 by anihamba          #+#    #+#             */
/*   Updated: 2025/04/16 14:16:05 by anihamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	append(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buff = buf;
	new_node->next = NULL;
}

char	*get_the_line(t_list *list)
{
	int		str_len;
	char	*next;

	if (!list || !list->str_buff)
		return (NULL);
	str_len = length_of_new_line(list);
	next = malloc(str_len + 1);
	if (!next)
		return (NULL);
	str_copy(list, next);
	return (next);
}

void	polish_the_list(t_list **list)
{
	t_list	*clean_node;
	t_list	*last_node;
	int		i;
	int		j;
	char	*buf;

	i = 0;
	j = 0;
	clean_node = malloc(sizeof(t_list));
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf || !clean_node)
		return ;
	last_node = find_last_node(*list);
	if (!last_node || !last_node->str_buff)
		return ;
	while (last_node->str_buff[j] && last_node->str_buff[j] != '\n')
		++j;
	while (last_node->str_buff[j] && last_node->str_buff[++j])
		buf[i++] = last_node->str_buff[j];
	buf[i] = '\0';
	clean_node->str_buff = buf;
	clean_node->next = NULL;
	free_the_list(list, clean_node, buf);
}

void	create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buf;

	while (!has_new_line(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read == 0)
		{
			free(buf);
			return ;
		}
		if (char_read < 0)
		{
			free(buf);
			free_the_list(list, NULL, NULL);
			return ;
		}
		buf[char_read] = '\0';
		append(list, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*lists[OPEN_MAX];
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
	{
		free_the_list(&lists[fd], NULL, NULL);
		return (NULL);
	}
	create_list(&lists[fd], fd);
	if (!lists[fd])
		return (NULL);
	next_line = get_the_line(lists[fd]);
	if (!next_line)
	{
		free_the_list(&lists[fd], NULL, NULL);
		return (NULL);
	}
	polish_the_list(&lists[fd]);
	return (next_line);
}

// #include <fcntl.h>
// #include <unistd.h>
// #include <stdio.h>
// int main()
// {
// 	int fd = open("get_next_line_bonus.c", O_RDONLY);
// 	char *line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = NULL;
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }
