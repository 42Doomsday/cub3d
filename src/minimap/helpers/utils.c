/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:11:45 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/11 16:55:19 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_block_size(t_map *map, int32_t width, int32_t height)
{
	int	size1;
	int	size2;

	size1 = width / map->width;
	size2 = height / map->height;
	if (size1 < size2)
		return (size1);
	return (size2);
}

t_vec2	get_player_vector(t_player *player)
{
	t_vec2	coords;

	coords.x = player->coords.x;
	coords.y = player->coords.y;
	return (coords);
}

/**
 * @brief Converts a player rotation angle (degrees) into a world-space
 *        movement direction vector of unit length.
 *
 * Rotation is measured clockwise from north (0° = up, 90° = right).
 * The angle is converted to standard mathematical convention before
 * being passed to cosf() and sinf().
 *
 * @param rotation  Player's current rotation in degrees.
 * @return          Normalised direction vector (dx, dy).
 */
t_vec2	direction_from_angle(float rotation)
{
	t_vec2	dir;
	float	radians;

	radians = (90.0f - rotation) * M_PI / 180.0f;
	dir.x = cosf(radians);
	dir.y = -sinf(radians);
	return (dir);
}
