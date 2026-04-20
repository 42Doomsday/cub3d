/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   degree_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 12:57:19 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/20 13:35:32 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_degree(t_cub3d *info, int change)
{
	int	new_degree;

	new_degree = info->player->dir.degree + (change * info->mlx->delta_time);
	update_player_degree(info->player, new_degree);
	calculate_angles(info->rays, info->player);
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
