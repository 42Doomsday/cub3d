/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 12:34:00 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/23 17:25:24 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	find_border_idx(char **map, int flag);
static int	count_idx(char *line, int flag);
static int	get_last_idx(char *line);

#define UNDEFINT -1
#define LEADING 0
#define TRAILING 1

void	trim_spaces(t_map *map)
{
	char	**data;
	int		border_idx;
	size_t	size;
	int		idx;

	data = map->data;
	border_idx = find_border_idx(map->data, LEADING);
	idx = 0;
	while (data && data[idx] && border_idx != 0)
	{
		size = ft_strlen(data[idx]) - border_idx + 1;
		ft_memmove(data[idx], data[idx] + border_idx, size);
		idx++;
	}
	border_idx = find_border_idx(map->data, TRAILING);
	idx = 0;
	while (data && data[idx])
	{
		if (border_idx < (int)ft_strlen(data[idx]))
			data[idx][border_idx] = '\0';
		idx++;
	}
}

static int	find_border_idx(char **map, int flag)
{
	int	total;
	int	border_idx;
	int	idx;

	total = UNDEFINT;
	idx = 0;
	while (map && map[idx])
	{
		border_idx = count_idx(map[idx], flag);
		if (total == UNDEFINT)
			total = border_idx;
		else if (flag == LEADING && border_idx < total)
			total = border_idx;
		else if (flag == TRAILING && border_idx > total)
			total = border_idx;
		idx++;
	}
	return (total);
}

static int	count_idx(char *line, int flag)
{
	int	idx;

	if (line == NULL)
		return (0);
	if (flag == LEADING)
	{
		idx = 0;
		while (line[idx] && line[idx] == SPACE)
			idx++;
	}
	else
	{
		idx = get_last_idx(line);
		while (idx >= 0 && line[idx] == SPACE)
			idx--;
		idx++;
	}
	return (idx);
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
