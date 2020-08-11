/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 13:34:27 by froxanne          #+#    #+#             */
/*   Updated: 2020/06/16 16:01:53 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

typedef struct	s_list
{
	int			fd;
	char		**strings;
	int			max_size;
	int			counter;
	void		*next;
	void		*prev;
}				t_list;

void			ft_lstdelone(t_list *list, t_list **first);
t_list			*ft_newlst(int fd, t_list *prev_node);
char			*ft_strdup(char const *str, int mode);
char			*ft_strjoin(char const *s1, char const *s2);
int				get_next_line(int fd, char **line);

#endif
