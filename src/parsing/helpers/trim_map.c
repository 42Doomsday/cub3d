/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 11:05:56 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/05 14:09:54 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	trim_empty_lines(t_map *map);
static bool	is_empty_line(char *line);

bool	trim_map(t_map *map)
{
	trim_empty_lines(map);
	trim_spaces(map);
	return (true);
}

static void	trim_empty_lines(t_map *map)
{
	char	**data;
	size_t	size;
	int		idx;

	idx = 0;
	data = map->data;
	while (data && data[idx])
	{
		if (is_empty_line(data[idx]))
		{
			free(data[idx]);
			size = (map->height - idx) * sizeof(char *);
			ft_memmove(data + idx, data + idx + 1, size);
			map->height--;
			continue ;
		}
		idx++;
	}
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
