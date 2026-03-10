/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:00:03 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/10 17:13:45 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	is_player(int c);
static void	set_params(t_player *player, int x, int y, char **map);
static bool	is_already_found(bool flag);

bool	parse_player(char **map, t_player *player)
{
	bool	found;
	int		i;
	int		j;

	if (map == NULL || player == NULL)
		return (false);
	i = 0;
	found = false;
	while (map && map[i])
	{
		j = 0;
		while (map[i] && map[i][j])
		{
			if (is_player(map[i][j]))
			{
				if (is_already_found(found))
					return (false);
				set_params(player, j, i, map);
				found = true;
			}
			j++;
		}
		i++;
	}
	return (found);
}

static bool	is_player(int c)
{
	return (ft_strchr(VALID_PLAYER_SIDES, c));
}

static bool	is_already_found(bool flag)
{
	return (flag == true);
}

static void	set_params(t_player *player, int x, int y, char **map)
{
	char	side;

	side = map[y][x];
	if (side == 'N')
		player->dir = 0;
	else if (side == 'E')
		player->dir = 90;
	else if (side == 'S')
		player->dir = 180;
	else if (side == 'W')
		player->dir = 270;
	player->y = y;
	player->x = x;
	map[y][x] = '0';
}
