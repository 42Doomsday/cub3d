/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:35:58 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/12 17:26:20 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_list	*read_to_list(int fd);
static bool		is_valid_char(char ch);
static bool		is_space(int c);

bool	parse_map(int fd, t_map *map, t_player *player)
{
	t_list	*lst;

	lst = read_to_list(fd);
	if (is_valid_chars(lst) == false)
	{
		ft_lstclear(&lst, free);
		return (false);
	}

	return (true);
}

static char **form_map(t_list *lst)
{
	ft_lstiter(lst, extend_tab());
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
		node = ft_lstnew(line);
		if (node == NULL)
		{
			ft_lstclear(lst, free);
			return (NULL);
		}
		ft_lstadd_back(&lst, node);
	}
	return (lst);
}

static bool is_valid_chars(char *str)
{
	while (str && *str)
	{
		if (is_valid_char(*str) == false)
			return (false);
		str++;
	}
	return (true);
}

static bool	is_space(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

static bool	is_valid_char(char ch)
{
	return (
		is_space(ch) ||
		ch == '0' ||
		ch == '1' ||
		ch == 'N' ||
		ch == 'E' ||
		ch == 'W' ||
		ch == 'S'
	);
}
