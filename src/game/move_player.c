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

void	move_player(t_world *world, float degree, double delta)
{
	t_coords	displacement;
	t_vec2		normilized;
	t_coords	wall;
	float		radians;
	float		dist_to_wall;
	float		dist_to_new_coords;

	radians = convert_degree_to_radians(degree);
	normilized = normilize(world->player->dir.radians + radians);

	wall = cast_ray_to_wall(world->player->coords, normilized, world->map);
	dist_to_wall = get_dist_to_wall(world->player->coords, wall);
	dist_to_new_coords = PLAYER_STEP * delta;
	if (dist_to_new_coords > dist_to_wall)
	{
		dist_to_new_coords = dist_to_wall;
		if (dist_to_new_coords < PLAYER_HITBOX_R * 2)
			return ;
	}

	displacement.x = normilized.x * (dist_to_new_coords);
	displacement.y = normilized.y * (dist_to_new_coords);
	world->player->coords.y = resolve_y(
			world->map,
			displacement.y,
			world->player->coords.x,
			world->player->coords.y + displacement.y
			);
	world->player->coords.x = resolve_x(
			world->map,
			displacement.x,
			world->player->coords.x + displacement.x,
			world->player->coords.y
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
