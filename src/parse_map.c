/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:35:58 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/19 17:29:32 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_rows(char **lines);
static int	max_strlen(char **lines);
static bool	is_closed(char **map, int size);
static bool	is_valid_chars(char **lines);

#define FILL '2'

bool	parse_map(int fd, t_map *map, t_player *player)
{
	char	**lines;

	if (map && player)
	{
		lines = read_lines(fd);
		if (lines)
		{
			map->data = lines;
			map->height = count_rows(lines);
			map->width = max_strlen(lines);
			return (
				is_valid_chars(lines)
				&& parse_player(map->data, player)
				&& is_closed(map->data, map->width)
			);
		}
	}
	return (false);
}

static int	count_rows(char **lines)
{
	int	counter;

	counter = 0;
	while (lines && lines[counter])
		counter++;
	return (counter);
}

static bool	is_closed(char **map, int size)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (i == 0 || i == size - 1 || j == 0 || map[i][j + 1] == '\0')
					return (false);
				if (map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
					return (false);
				if (map[i][j + 1] == ' ' || (j > 0 && map[i][j - 1] == ' '))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

static bool	is_contiguous(char **map, int size)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr(MAP_CHARACTERS, map[i][j]) == true)
				flood_fill(map, i, j);
			j++;
		}
		i++;
	}
	return (true);
}

static char **flood_fill(t_map *map, int i, int j)
{
	t_list		*queue;
	t_coords	*coords;

	queue = NULL;
	add_back(queue, i, j);
	while (ft_lstsize(queue) > 0)
	{
		coords = pop(&queue);
		map->data[coords->y][coords->x] = FILL;
		add_neighbors(&queue, map, coords);
		free(coords);
	}
}

static bool	add_back(t_list **queue, int i, int j)
{
	t_coords	*coords;
	t_list		*node;

	coords = malloc(sizeof(t_coords));
	if (coords)
	{
		coords->x = j;
		coords->y = i;
		node = ft_lstnew(coords);
		if (node)
		{
			ft_lstadd_back(queue, node);
			return (true);
		}
		free(coords);
	}
	return (false);
}

t_coords	*pop(t_list **queue)
{
	t_list		*node;
	t_coords	*coords;

	node = *queue;
	*queue = (*queue)->next;
	coords = node->content;
	free(node);
	return (coords);
}

static bool	is_valid(t_map *map, t_coords *coords)
{
	int		x;
	int		y;
	char	**data;

	data = map->data;
	x = coords->x;
	y = coords->y;
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (false);
	if (data[y][x] != FILL && data[y][x] != ' ')
		return (false);
	return (true);
}

static void add_neighbors(t_list **queue, t_map *map, t_coords *coords)
{
	int dx[4] = {1, -1, 0, 0};
	int dy[4] = {0, 0, 1, -1};
	int k;
	int nx;
	int ny;

	k = 0;
	while (k < 4)
	{
		nx = coords->x + dx[k];
		ny = coords->y + dy[k];
		if (is_valid(map, coords))
			add_back(queue, ny, nx);
		k++;
	}
}

static int	max_strlen(char **lines)
{
	int	max;
	int	len;
	int	idx;

	max = -1;
	idx = 0;
	while (lines && lines[idx])
	{
		len = ft_strlen(lines[idx]);
		if (len > max)
			max = len;
		idx++;
	}
	return (max);
}

static bool	is_valid_chars(char **lines)
{
	char	*str;
	int		idx;

	idx = 0;
	while (lines && lines[idx])
	{
		str = lines[idx];
		while (str && *str)
		{
			if (ft_strchr(VALID_CHARS_MAP, *str) == false)
				return (false);
			str++;
		}
		idx++;
	}
	return (true);
}
