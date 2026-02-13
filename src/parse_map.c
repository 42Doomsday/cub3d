/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:35:58 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/13 17:45:10 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define TAB_SIZE 4

static t_list	*read_to_list(int fd);
static void		expand_tabs(t_list *lst);
static bool		is_valid_chars(t_list *lst);
static char		**convert_to_array(t_list *lst, size_t size);
static int		max_length(t_list *lst);
static bool		is_closed(char **map, int size);
static bool		find_player(char **map, t_player *player);
static bool		is_valid_char(char ch);
static bool		is_space(int c);

bool	parse_map(int fd, t_map *map, t_player *player)
{
	t_list	*lst;

	lst = read_to_list(fd);
	if (lst == NULL)
		return (false);
	expand_tabs(lst);
	if (is_valid_chars(lst) == false)
	{
		ft_lstclear(&lst, NULL);
		return (false);
	}
	map->height = ft_lstsize(lst);
	map->data = convert_to_array(lst, map->height);
	map->width = max_length(lst);
	if (is_closed(map->data, map->height) == false)
	{
		ft_lstclear(&lst, NULL);
		return (false);
	}
	if (find_player(map->data, player) == false)
	{
		ft_lstclear(&lst, NULL);
		return (false);
	}
	ft_lstclear(&lst, NULL);
	return (true);
}

static void	expand_tabs(t_list *lst)
{
	char	*str;
	char	*new_str;
	int		counter;
	int		idx;

	while (lst)
	{
		str = lst->content;
		idx = 0;
		counter = 0;
		while (str && str[idx])
		{
			if (str[idx] == '\t')
				counter += TAB_SIZE;
			else
				counter++;
			idx++;
		}
		if (idx != counter)
		{
			new_str = malloc(counter + 1);
			int	i;
			int	k;
			int	j;
			i = 0;
			k = 0;
			j = 0;
			while (str && str[i])
			{
				if (str[i] == '\t')
				{
					k = 0;
					while (k < TAB_SIZE)
					{
						new_str[j++] = ' ';
						k++;
					}
				}
				else
					new_str[j++] = str[i];
				i++;
			}
			new_str[j] = '\0';
			free(str);
			lst->content = new_str;
		}
		lst = lst->next;
	}
}

static bool is_closed(char **map, int size)
{
	int	i;
	int	j;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '0')
			{
				if (i == 0 || i == size - 1 || j == 0 || map[i][j + 1] == '\0')
					return (false);
				else
				{
					if (map[i + 1][j] == ' ')
						return (false);
					if (map[i - 1][j] == ' ')
						return (false);
					if (map[i][j + 1] == ' ')
						return (false);
					if (j > 0 && map[i][j - 1] == ' ')
						return (false);
				}
			}
			j++;
		}
		i++;
	}
	return (true);
}

static char	**convert_to_array(t_list *lst, size_t size)
{
	char	**data;
	int		idx;

	data = malloc((size + 1) * sizeof(char *));
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

static int	max_length(t_list *lst)
{
	int	max;
	int	len;

	max = -1;
	while (lst)
	{
		len = ft_strlen(lst->content);
		if (len > max)
			max = len;
		lst = lst->next;
	}
	return (max);
}

static bool	find_player(char **map, t_player *player)
{
	bool	found;
	int		i;
	int		j;
	char	c;

	i = 0;
	found = false;
	while (map && map[i])
	{
		j = 0;
		while (map[i] && map[i][j])
		{
			c = map[i][j];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			{
				if (found)
					return (false);
				player->side = c;
				player->y = i;
				player->x = j;
				found = true;
			}
			j++;
		}
		i++;
	}
	return (found);
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

static bool is_valid_chars(t_list *lst)
{
	char	*str;

	while (lst)
	{
		str = lst->content;
		while (str && *str)
		{
			if (is_valid_char(*str) == false)
				return (false);
			str++;
		}
		lst = lst->next;
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
