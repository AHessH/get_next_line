/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 13:34:15 by froxanne          #+#    #+#             */
/*   Updated: 2020/06/14 13:08:01 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*ft_newlst(int fd, t_list *prev_node)
{
	t_list	*node;

	if (!(node = (t_list *)malloc(sizeof(t_list))))
		return (0);
	node->fd = fd;
	node->counter = 0;
	node->max_size = 1;
	node->strings = 0;
	node->next = 0;
	node->prev = (t_list *)prev_node;
	return (node);
}

void	ft_lstdelone(t_list *list, t_list **first)
{
	t_list	*tmp;

	tmp = list->prev;
	free(list->strings);
	list->strings = 0;
	if (tmp)
		tmp->next = list->next;
	else
		*first = list->next;
	list->max_size = 0;
	list->next = 0;
	list->prev = 0;
	free(list);
}

int		ft_strlen(char const *str)
{
	int len;

	len = 0;
	while (str && *str++)
		len++;
	return (len);
}

char	*ft_strdup(char const *str, int mode)
{
	int		len;
	int		i;
	char	*copy;

	i = 0;
	len = 0;
	if (!mode)
		len = ft_strlen(str);
	if (mode)
		if (!str || str[i] == '\n')
			len = 0;
	while (mode && str && str[i] && str[i++] != '\n')
		len++;
	if (!(copy = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	i = -1;
	while (++i < len)
		copy[i] = str[i];
	copy[i] = 0;
	return (copy);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	int		i;
	char	*comb_str;

	i = 0;
	if (!s1 || !s2)
		return (comb_str = ft_strdup(!s1 ? s2 : s1, 0));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(comb_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (0);
	while (s1_len--)
		comb_str[i++] = *s1++;
	while (s2_len--)
		comb_str[i++] = *s2++;
	comb_str[i] = '\0';
	return (comb_str);
}
