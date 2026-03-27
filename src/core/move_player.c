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

static t_coords	get_new_player_position(t_player *player, t_vec2 unit_vector);
static t_vec2	get_coords_movement(t_vec2 unit_vector, float distance);
static t_vec2	get_new_unit_vector(t_player *player, float degree_change);
static float	get_new_rad_dir(t_player *player, float degree_change);

void	move_player(t_map *map, t_player *player, float degree)
{
	t_coords	new;
	t_vec2		unit_vector;
	t_coords	wall;

	unit_vector = get_new_unit_vector(player, degree);
	new = get_new_player_position(player, unit_vector);
	if (is_wall_or_space_on_coords(map, new.x, player->coords.y))
	{
		wall.x = new.x;
		wall.y = player->coords.y;
		if (unit_vector.x > 0)
			new.x = (float)(int)wall.x - PLAYER_HITBOX_R;
		else
			new.x = (float)((int)wall.x + 1) + PLAYER_HITBOX_R;
	}
	if (is_wall_or_space_on_coords(map, player->coords.x, new.y))
	{
		wall.x = player->coords.x;
		wall.y = new.y;
		if (unit_vector.y > 0)
			new.y = (float)(int)wall.x - PLAYER_HITBOX_R;
		else
			new.y = (float)((int)wall.y + 1) + PLAYER_HITBOX_R;
	}
	if (is_wall_or_space_on_coords(map, new.x, new.y))
		return ;
	player->coords = new;
}

static t_coords	get_new_player_position(t_player *player, t_vec2 unit_vector)
{
	t_coords	new_coords;
	t_vec2		movement;

	movement = get_coords_movement(unit_vector, PLAYER_STEP);
	new_coords.x = player->coords.x + movement.x;
	new_coords.y = player->coords.y + movement.y;
	return (new_coords);
}

static t_vec2	get_coords_movement(t_vec2 unit_vector, float distance)
{
	t_vec2	movement;

	movement.x = unit_vector.x * distance;
	movement.y = unit_vector.y * distance;
	return (movement);
}

static t_vec2	get_new_unit_vector(t_player *player, float degree_change)
{
	t_vec2	unit_vector;
	float	radians;

	radians = get_new_rad_dir(player, degree_change);
	unit_vector = normilize(radians);
	return (unit_vector);
}

static float	get_new_rad_dir(t_player *player, float degree_change)
{
	float	radians;

	radians = player->dir.radians + convert_degree_to_radians(degree_change);
	return (radians);
}
