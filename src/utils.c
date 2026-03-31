/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:11:45 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/31 16:59:03 by dkalgano         ###   ########.fr       */
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

void	update_player_degree(t_player *player, float degree)
{
	float	radians;

	player->dir.degree = degree;
	radians = convert_degree_to_radians(degree);
	player->dir.radians = radians;
	player->dir.unit = normilize(radians);
}

float	convert_degree_to_radians(float degree)
{
	return ((90.0f - degree) * M_PI / 180.0f);
}

t_vec2	normilize(float radians)
{
	t_vec2	unit_vector;

	unit_vector.x = cos(radians);
	unit_vector.y = -sin(radians);
	return (unit_vector);
}
