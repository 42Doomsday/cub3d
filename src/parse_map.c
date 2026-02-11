/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:35:58 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/11 12:43:58 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_space(int c);

bool	parse_map(int fd, t_map *map, t_player *player)
{
	char	*line;
	int		idx;

	while ((line = get_next_line(fd)) != NULL)
	{
		idx = 0;
		while (line && line[idx])
		{
			if (is_space(line[idx]))
			{
				idx++;
				continue ;
			}
			idx++;
		}
	}
	return (true);
}

bool	is_space(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}
