/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 11:05:56 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/23 11:51:40 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* static bool	trim_empty_lines(char **map, size_t size); */
static bool	is_empty_line(char *line);

/* bool	trim_map(t_map *map)
{
	char	**data;
	char	idx;

	data = map->data;
} */

bool	trim_empty_lines(t_map *map)
{
	char	**data;
	int		idx;

	idx = 0;
	data = map->data;
	while (data && data[idx])
	{
		if (is_empty_line(data[idx]))
		{
			free(data[idx]);
			ft_memmove(data + idx, data + idx + 1, (map->height - idx) * sizeof(char *));
			map->height--;
			continue ;
		}
		idx++;
	}
	return (true);
}

static bool	is_empty_line(char *line)
{
	int	idx;

	idx = 0;
	while (line && line[idx])
	{
		if (line[idx] != SPACE)
			return (false);
		idx++;
	}
	return (true);
}
