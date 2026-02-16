/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:35:58 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/16 15:35:49 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_rows(char **lines);
static int	max_strlen(char **lines);
static bool	is_closed(char **map, int size);
static bool	is_valid_chars(char **lines);

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
