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

static t_coords	get_displaced_coords(t_map *map, t_player *player, float degree)
{
	t_coords		new;
	t_coords		wall;
	t_vec2			normilized;
	float			radians;
	float			distance;
	t_texture_id	side;

	radians = convert_degree_to_radians(degree + player->dir.degree);
	normilized = normilize(radians);
	wall = cast_ray_to_wall(player->coords, radians, map);
	distance = get_dist_to_wall(player->coords, wall);
	side = get_side_of_wall(wall, normilized);
	printf("dist %f\n", distance);
	/* if (distance < PLAYER_HITBOX_R)
	{
		printf("enters\n");
		new.x = 0;
		new.y = 0;
		return (new);
	} */
	/* if (distance < PLAYER_HITBOX_R)
	{
		if (side == NORTH || side == SOUTH)
		{
			if (player->dir.unit.y > 0)
				new.y = (float)((int)new.y + 1) + PLAYER_HITBOX_R;
			else
				new.y = (float)(int)new.y - PLAYER_HITBOX_R;
			new.x = player->coords.x + (normilized.x * PLAYER_R);
		}
		else
		{
			if (player->dir.unit.x > 0)
				new.x = (float)(int)new.x - PLAYER_HITBOX_R;
			else
				new.x = (float)((int)new.x + 1) + PLAYER_HITBOX_R;
			new.y = player->coords.y + (normilized.y * PLAYER_R);
		}
	}
	else
	{
		new.x = player->coords.x + (normilized.x * PLAYER_R);
		new.y = player->coords.y + (normilized.y * PLAYER_R);
	} */
	new.x = player->coords.x + (normilized.x * PLAYER_R);
	new.y = player->coords.y + (normilized.y * PLAYER_R);
	return (new);
}

/* static float	min(float f, float s)
{
	if (f < s)
		return (f);
	return (s);
} */

void	move_player(t_map *map, t_player *player, float degree)
{
	t_coords	points[3];
	t_coords	walls[3];
	float		dists[3];
	float		radians;
	float		nearest;

	printf("---------------------\n");
	points[0] = get_displaced_coords(map, player, degree + -90);
	points[1] = player->coords;
	points[2] = get_displaced_coords(map, player, degree + 90);

	/* if ((points[0].x < EPS || points[0].y < EPS))
		return ;

	if (points[1].x < EPS || points[1].y < EPS)
		return ;

	if ((points[2].x < EPS || points[2].y < EPS))
		return ; */

	radians = convert_degree_to_radians(degree + player->dir.degree);
	walls[0] = cast_ray_to_wall(points[0], radians, map);
	walls[1] = cast_ray_to_wall(points[1], radians, map);
	walls[2] = cast_ray_to_wall(points[2], radians, map);

	dists[0] = get_dist_to_wall(points[0], walls[0]);
	dists[1] = get_dist_to_wall(points[1], walls[1]);
	dists[2] = get_dist_to_wall(points[2], walls[2]);

	printf("p1 (right) %f %f\n", points[0].x, points[0].y);
	printf("p2 (center) %f %f\n", points[1].x, points[1].y);
	printf("p3 (left) %f %f\n", points[2].x, points[2].y);

	printf("dists[0] %f \n", dists[0]);
	printf("dists[1] %f \n", dists[1]);
	printf("dists[2] %f \n", dists[2]);

	printf("w1 %f %f\n", walls[0].x, walls[0].y);
	printf("w2 %f %f\n", walls[2].x, walls[2].y);

	t_texture_id	side;
	t_vec2			normilized;
	t_coords		wall;

	normilized = normilize(radians);
	if ((dists[0] < dists[1]) && (dists[0] < dists[2]))
	{
		nearest = dists[0] - PLAYER_R / 2;
		wall = walls[0];
		side = get_side_of_wall(walls[0], normilized);
	}
	else if ((dists[1] < dists[0]) && (dists[1] < dists[2]))
	{
		nearest = dists[1];
		wall = walls[1];
		side = get_side_of_wall(walls[1], normilized);
	}
	else
	{
		nearest = dists[2] - PLAYER_R / 2;
		wall = walls[2];
		side = get_side_of_wall(walls[2], normilized);
	}

	printf("neares: %f\n", nearest);

	if (nearest > PLAYER_HITBOX_R)
	{
		player->coords.x += (normilized.x * PLAYER_STEP);
		player->coords.y += (normilized.y * PLAYER_STEP);
	}
	else
	{
		printf("I should do smth here\n");
		if (side == NORTH || side == SOUTH)
		{
			if (normilized.y < 0)
				player->coords.y = (float)((int)wall.y) + PLAYER_HITBOX_R;
			else
				player->coords.y = (float)(int)wall.y - PLAYER_HITBOX_R;
			player->coords.x += (normilized.x * PLAYER_STEP);
		}
		else
		{
			if (normilized.x > 0)
				player->coords.x = (float)(int)wall.x - PLAYER_HITBOX_R;
			else
				player->coords.x = (float)((int)wall.x) + PLAYER_HITBOX_R;
			player->coords.y += (normilized.y * PLAYER_STEP);
		}
	}
	printf("new coords %f %f\n", player->coords.x, player->coords.y);
}
