/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:03:45 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/07 15:17:59 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "coords.h"

typedef struct s_map
{
	char	**data;
	int		height;
	int		width;
}	t_map;

typedef struct s_direction
{
	float	degree;
	float	radians;
	t_vec2	unit;
}	t_direct;

typedef struct s_player
{
	t_direct	dir;
	t_coords	coords;
}	t_player;

void	update_player_degree(t_player *player, float degree);
void	free_map_data(char **data);
void	free_map(t_map *map);

#endif
