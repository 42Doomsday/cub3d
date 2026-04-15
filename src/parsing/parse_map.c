/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:35:58 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/07 14:25:46 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	count_rows(char **lines);
static int	max_strlen(char **lines);
static bool	is_valid_map(t_map *map, t_player *player);
static bool	is_valid_chars(char **lines);

bool	parse_map(int fd, t_map *map, t_player *player)
{
	char	**lines;
	bool	is_valid;

	is_valid = false;
	if (map && player)
	{
		lines = read_lines(fd);
		if (lines)
		{
			map->data = lines;
			map->height = count_rows(lines);
			map->width = max_strlen(lines);
			is_valid = is_valid_map(map, player);
		}
	}
	return (is_valid);
}

static int	count_rows(char **lines)
{
	int	counter;

	counter = 0;
	while (lines && lines[counter])
		counter++;
	return (counter);
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

static bool	is_valid_map(t_map *map, t_player *player)
{
	return (
		msg_on_error(is_valid_chars(map->data), PARSER, INV_CHARS)
		&& msg_on_error(is_closed(map->data, map->height), PARSER, ISNT_CLOSED)
		&& msg_on_error(is_contiguous(map), PARSER, ISNT_CONTIGUOUS)
		&& trim_map(map)
		&& msg_on_error(parse_player(map->data, player), PARSER, INV_PLAYER)
	);
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
