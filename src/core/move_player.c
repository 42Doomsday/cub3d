/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <dkalgano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by dkalgano         #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by dkalgano        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	resolve_x(t_map *map, float dx, float new_x, float cur_y);
static float	resolve_y(t_map *map, float dy, float cur_x, float new_y);

void	move_player(t_cub3d *info, float degree)
{
	t_coords	displacement;
	t_vec2		normilized;
	float		radians;

	radians = convert_degree_to_radians(degree);
	normilized = normilize(info->player.dir.radians + radians);
	displacement.x = normilized.x * (PLAYER_STEP * info->mlx->delta_time);
	displacement.y = normilized.y * (PLAYER_STEP * info->mlx->delta_time);
	info->player.coords.y = resolve_y(
			&info->map,
			displacement.y,
			info->player.coords.x,
			info->player.coords.y + displacement.y
			);
	info->player.coords.x = resolve_x(
			&info->map,
			displacement.x,
			info->player.coords.x + displacement.x,
			info->player.coords.y
			);
}

static float	resolve_x(t_map *map, float dx, float new_x, float cur_y)
{
	int	tile_x;
	int	tile_y;

	if (dx > 0)
		tile_x = (int)floorf(new_x + PLAYER_HITBOX_R);
	else
		tile_x = (int)floorf(new_x - PLAYER_HITBOX_R);
	tile_y = (int)cur_y;
	if (is_wall_or_space_on_coords(map, tile_x, tile_y))
	{
		if (dx > 0)
			return (tile_x - PLAYER_HITBOX_R);
		return (tile_x + 1 + PLAYER_HITBOX_R);
	}
	return (new_x);
}

static float	resolve_y(t_map *map, float dy, float cur_x, float new_y)
{
	int	tile_y;
	int	tile_x;

	if (dy > 0)
		tile_y = (int)floorf(new_y + PLAYER_HITBOX_R);
	else
		tile_y = (int)floorf(new_y - PLAYER_HITBOX_R);
	tile_x = (int)cur_x;
	if (is_wall_or_space_on_coords(map, tile_x, tile_y))
	{
		if (dy > 0)
			return (tile_y - PLAYER_HITBOX_R);
		return (tile_y + 1 + PLAYER_HITBOX_R);
	}
	return (new_y);
}
