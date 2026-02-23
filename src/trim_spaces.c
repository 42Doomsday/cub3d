/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 12:34:00 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/23 12:56:32 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_extra_spaces(char **map, int flag);
static int	count_spaces(char *line, int flag);
static int	get_last_idx(char *line);

#define UNDEFINT -1
#define LEADING 0
#define TRAILING 1

bool	trim_spaces(t_map *map)
{
	char	**data;
	int		count;
	size_t	size;
	int		idx;

	data = map->data;
	count = count_extra_spaces(map->data, LEADING);
	idx = 0;
	while (data && data[idx])
	{
		size = ft_strlen(data[idx]) - count + 1;
		ft_memmove(data[idx], data[idx] + count, size);
		idx++;
	}
	count = count_extra_spaces(map->data, TRAILING);
	idx = 0;
	while (data && data[idx])
	{
		data[idx][ft_strlen(data[idx]) - count] = '\0';
		idx++;
	}
	return (true);
}

static int	count_extra_spaces(char **map, int flag)
{
	int	total;
	int	count;
	int	idx;

	total = UNDEFINT;
	idx = 0;
	while (map && map[idx])
	{
		count = count_spaces(map[idx], flag);
		if (total == UNDEFINT || count < total)
			total = count;
		idx++;
	}
	return (total);
}

static int	count_spaces(char *line, int flag)
{
	int	count;
	int	idx;

	count = 0;
	if (flag == LEADING)
		idx = 0;
	else
		idx = get_last_idx(line);
	while (42)
	{
		if (flag == LEADING && line[idx] == '\0')
			break ;
		if (flag == TRAILING && idx >= 0)
			break ;
		if (line[idx] == SPACE)
			count++;
		if (flag == LEADING)
			idx++;
		else
			idx--;
	}
	return (count);
}

static int	get_last_idx(char *line)
{
	int	idx;

	idx = -1;
	if (line)
	{
		idx = ft_strlen(line);
		if (idx > 0)
			idx -= 1;
	}
	return (idx);
}
