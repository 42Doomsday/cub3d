/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_closed.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:01:18 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/02 17:13:35 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	is_border_coord(char **map, int height, int x, int y);
static bool	is_char_or_null(char **map, int x, int y, char ch);
static char	*get(char **map, int x, int y);
static bool	is_valid_coord(char **map, int x, int y);

bool	is_closed(char **map, int height)
{
	int		x;
	int		y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == WALL)
			{
				if (is_border_coord(map, height, x, y))
					return (false);
				if (is_char_or_null(map, x, y + 1, SPACE))
					return (false);
				if (is_char_or_null(map, x, y - 1, SPACE))
					return (false);
				if (map[y][x + 1] == SPACE || (x > 0 && map[y][x - 1] == SPACE))
					return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}

static bool	is_border_coord(char **map, int height, int x, int y)
{
	if (y == 0 || y == height - 1 || x == 0 || map[y][x + 1] == '\0')
		return (true);
	return (false);
}

static bool	is_char_or_null(char **map, int x, int y, char ch)
{
	char	*result;

	result = get(map, x, y);
	if (result == NULL)
		return (true);
	if (*result == ch)
		return (true);
	return (false);
}

static char	*get(char **map, int x, int y)
{
	if (is_valid_coord(map, x, y))
		return (&map[y][x]);
	return (NULL);
}

static bool	is_valid_coord(char **map, int x, int y)
{
	int	size;

	if (map == NULL || map[y] == NULL)
		return (false);
	size = ft_strlen(map[y]);
	if (x >= size)
		return (false);
	return (true);
}
