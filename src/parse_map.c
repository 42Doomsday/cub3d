/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:35:58 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/16 14:37:58 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_rows(char **lines);
static int	max_strlen(char **lines);
static bool	parse_player(t_map *map, t_player *player);
static bool is_closed(t_map *map);
static bool is_valid_chars(char **lines);
static bool	is_valid_char(char ch);
static bool	is_space(int c);

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
				is_valid_chars(lines) &&
				parse_player(map, player) &&
				is_closed(map)
			);
		}
	}
	return (false);
}

static bool	parse_player(t_map *map, t_player *player)
{
	bool	found;
	int		i;
	int		j;
	char	c;

	i = 0;
	found = false;
	while (map->data && map->data[i])
	{
		j = 0;
		while (map->data[i] && map->data[i][j])
		{
			c = map->data[i][j];
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

static int	count_rows(char **lines)
{
	int	counter;

	counter = 0;
	while (lines && lines[counter])
		counter++;
	return (counter);
}

static bool is_closed(t_map *map_info)
{
	char	**map;
	int		size;
	int		i;
	int		j;

	i = 0;
	size = map_info->height;
	map = map_info->data;
	while (map[i])
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

static bool is_valid_chars(char **lines)
{
	char	*str;
	int		idx;

	idx = 0;
	while (lines && lines[idx])
	{
		str = lines[idx];
		while (str && *str)
		{
			if (is_valid_char(*str) == false)
				return (false);
			str++;
		}
		idx++;
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
