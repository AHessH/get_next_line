/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 13:34:24 by froxanne          #+#    #+#             */
/*   Updated: 2020/07/21 15:13:56 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		free_memory(t_list **list)
{
	int		i;
	t_list	*node;
	t_list	*tmp;

	if (list && *list)
	{
		node = *list;
		i = 0;
		while (node)
		{
			while (node->strings && node->strings[i])
				free(node->strings[i++]);
			free(node->strings);
			tmp = node;
			node = node->next;
			free(tmp);
		}
	}
	return (-1);
}

int		split_f_string(char *str, t_list *node)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = str;
	if (!(node->strings = (char **)malloc(sizeof(char *) * node->max_size)))
		return (0);
	j = node->max_size;
	if (!str)
		if (!(node->strings[0] = ft_strdup("", 0)))
			return (0);
	while (str && j--)
	{
		if (!(node->strings[i] = ft_strdup(str, 1)))
			return (0);
		while (*str && *str != '\n')
			str++;
		str++;
		i++;
	}
	free(tmp);
	return (1);
}

int		read_file(t_list *list)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*tmp;
	int		i;
	char	*full_str;

	full_str = 0;
	while ((i = read(list->fd, buffer, BUFFER_SIZE)))
	{
		buffer[i] = 0;
		tmp = full_str;
		if (!(full_str = ft_strjoin(full_str, buffer)))
			return (0);
		free(tmp);
	}
	i = 0;
	while (full_str)
	{
		while (full_str[i] && full_str[i] != '\n')
			i++;
		if (!(full_str[i]))
			break ;
		list->max_size++;
		i++;
	}
	return (split_f_string(full_str, list));
}

int		ret_str(t_list **first, t_list *node, char **line)
{
	if (node->counter != node->max_size && node->max_size != -2)
	{
		if (!(*line = ft_strdup(node->strings[node->counter], 0)))
			return (free_memory(first));
		free(node->strings[node->counter]);
		node->counter++;
		if (node->counter != node->max_size)
			return (1);
	}
	ft_lstdelone(node, first);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static t_list		*first;
	t_list				*list;
	char				check;

	if (BUFFER_SIZE < 1 || fd < 0 || !line || read(fd, &check, 0) < 0)
		return (-1);
	if (!first)
		if (!(first = ft_newlst(fd, 0)))
			return (-1);
	list = first;
	while (list->fd != fd)
	{
		if (!list->next)
			if (!(list->next = ft_newlst(fd, list)))
				return (free_memory(&first));
		list = list->next;
	}
	if (list->max_size == 1 && !(read_file(list)))
		return (free_memory(&first));
	return (ret_str(&first, list, line));
}
