/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:53:25 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/16 16:51:19 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_list	*read_to_list(int fd);
static char		**convert_to_array(t_list *lst);

char	**read_lines(int fd)
{
	char	**map;
	t_list	*lst;

	map = NULL;
	lst = read_to_list(fd);
	if (lst)
	{
		lst = expand_tabs(lst);
		if (lst)
		{
			map = convert_to_array(lst);
			ft_lstclear(&lst, NULL);
		}
	}
	return (map);
}

static t_list	*read_to_list(int fd)
{
	t_list	*lst;
	t_list	*node;
	char	*line;

	lst = NULL;
	while (42)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		line[ft_strlen(line) - 1] = '\0';
		node = ft_lstnew(line);
		if (node == NULL)
		{
			ft_lstclear(&lst, free);
			return (NULL);
		}
		ft_lstadd_back(&lst, node);
	}
	return (lst);
}

static char	**convert_to_array(t_list *lst)
{
	char	**data;
	int		idx;

	if (lst == NULL)
		return (NULL);
	data = malloc((ft_lstsize(lst) + 1) * sizeof(char *));
	if (data == NULL)
		return (NULL);
	idx = 0;
	while (lst)
	{
		data[idx] = lst->content;
		lst = lst->next;
		idx++;
	}
	data[idx] = NULL;
	return (data);
}
