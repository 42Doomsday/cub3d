/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <dkalgano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by dkalgano         #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by dkalgano        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool			is_wall(t_vec2 coords, t_vec2 unit_vector, t_map *map);
float			find_dist(t_vec2 origin, t_vec2 unit_vector, bool coord);
static t_vec2	is_on_edges(t_vec2 coords);
static int		get_block_coord(bool on_edge, float current, float unit_value);
t_vec2			normilize(float angle);

float	get_dist_to_wall(t_vec2 origin, float angle, t_map *map)
{
	t_vec2	wall;
	t_vec2	unit_vector;
	float	dist_x;
	float	dist_y;
	float	dist;

	wall = cast_ray_to_wall(origin, angle, map);
	unit_vector = normilize(angle);
	dist_x = fabs(wall.x - origin.x);
	dist_y = fabs(wall.y - origin.y);
	dist = sqrt(dist_x * dist_x + dist_y * dist_y);
	return (dist);
}

t_vec2	cast_ray_to_wall(t_vec2 origin, float angle, t_map *map)
{
	t_vec2	curent_coords;
	t_vec2	unit_vector;

	curent_coords = origin;
	unit_vector = normilize(angle);
	while (42)
	{
		curent_coords = cast_ray_to_border(curent_coords, angle);
		int result = is_wall(curent_coords, unit_vector, map);
		if (result == 1 || result == 2)
			return (curent_coords);
	}
}

bool	is_wall(t_vec2 coords, t_vec2 unit_vector, t_map *map)
{
	t_vec2	on_edges;
	int		x;
	int		y;

	if (map->data[(int)floor(coords.y)][(int)floor(coords.x)] == '1')
		return (true);
	on_edges = is_on_edges(coords);
	x = get_block_coord(on_edges.x, coords.x, unit_vector.x);
	y = get_block_coord(on_edges.y, coords.y, unit_vector.y);
	if (x < 0 || y < 0 || y >= map->height || x >= map->width)
		return (true);
	return (map->data[y][x] == '1');
}

static t_vec2	is_on_edges(t_vec2 coords)
{
	t_vec2	result;

	result.x = fabs(coords.x - round(coords.x)) < 1e-6;
	result.y = fabs(coords.y - round(coords.y)) < 1e-6;
	return (result);
}

static int	get_block_coord(bool on_edge, float current, float unit_value)
{
	int	coord;

	if (on_edge && unit_value < 0)
		coord = (int)floor(current) - 1;
	else
		coord = (int)floor(current);
	return (coord);
}

t_vec2	cast_ray_to_border(t_vec2 origin, float angle)
{
	t_vec2	point;
	t_vec2	unit_vector;
	float	dist;
	float	dist_second;

	unit_vector = normilize(angle);
	dist = find_dist(origin, unit_vector, 0);
	dist_second = find_dist(origin, unit_vector, 1);
	if (dist_second < dist)
		dist = dist_second;
	point.x = origin.x + dist * unit_vector.x;
	point.y = origin.y + dist * unit_vector.y;
	return (point);
}

float	find_dist(t_vec2 origin, t_vec2 unit_vector, bool coord)
{
	float	origin_value;
	float	unit_value;
	float	destination;

	if (coord == 0)
	{
		origin_value = origin.x;
		unit_value = unit_vector.x;
	}
	else
	{
		origin_value = origin.y;
		unit_value = unit_vector.y;
	}
	if (unit_value == 0)
		return (1e30);
	if (unit_value > 0)
		destination = floor(origin_value) + 1.0f;
	else
	{
		destination = floor(origin_value);
		if (destination == origin_value)
			destination -= 1.0f;
	}
	return ((destination - origin_value) / unit_value);
}

t_vec2	normilize(float angle)
{
	t_vec2	unit_vector;

	unit_vector.x = cos(angle);
	unit_vector.y = -sin(angle);
	return (unit_vector);
}
