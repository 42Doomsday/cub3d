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

static t_coords	cast_ray_to_border(t_coords origin, float angle);
static float	find_dist(t_coords origin, t_vec2 unit_vector, bool coord);

float	get_dist_to_wall(t_coords origin, t_coords wall)
{
	float	dist_x;
	float	dist_y;
	float	dist;

	dist_x = fabs(wall.x - origin.x);
	dist_y = fabs(wall.y - origin.y);
	dist = sqrt(dist_x * dist_x + dist_y * dist_y);
	return (dist);
}

t_wall_info	cast_ray_to_wall(t_coords origin, float angle, t_map *map)
{
	t_wall_info	result;
	t_coords	ray_coords;
	t_vec2		unit_vector;

	ray_coords = origin;
	unit_vector = normilize(angle);
	while (42)
	{
		ray_coords = cast_ray_to_border(ray_coords, angle);
		if (is_wall(ray_coords, unit_vector, map))
		{
			result.coords = ray_coords;
			result.side = get_side_of_wall(ray_coords, unit_vector);
			return (result);
		}
	}
}

static t_coords	cast_ray_to_border(t_coords origin, float angle)
{
	t_coords	point;
	t_vec2		unit_vector;
	float		dist;
	float		dist_second;

	unit_vector = normilize(angle);
	dist = find_dist(origin, unit_vector, 0);
	dist_second = find_dist(origin, unit_vector, 1);
	if (dist_second < dist)
		dist = dist_second;
	point.x = origin.x + dist * unit_vector.x;
	point.y = origin.y + dist * unit_vector.y;
	return (point);
}

static float	find_dist(t_coords origin, t_vec2 unit_vector, bool coord)
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
