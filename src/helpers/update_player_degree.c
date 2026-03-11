/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_degree.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:41:49 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/11 16:58:31 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_vec2	normilize(float angle);
static float	convert_degree_to_radians(float degree);

void	update_player_degree(t_player *player, float degree)
{
	float	radians;

	player->dir.degree = degree;
	radians = convert_degree_to_radians(degree);
	player->dir.radians = radians;
	player->dir.unit = normilize(radians);
}

static float	convert_degree_to_radians(float degree)
{
	return ((90.0f - degree) * M_PI / 180.0f);
}

static t_vec2	normilize(float radians)
{
	t_vec2	unit_vector;

	unit_vector.x = cos(radians);
	unit_vector.y = -sin(radians);
	return (unit_vector);
}
