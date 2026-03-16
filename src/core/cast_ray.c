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

float	find_dist(t_vec2 origin, t_vec2 unit_vector, bool coord);
t_vec2	normilize(float angle);

float	get_dist_to_wall(t_vec2 origin, t_vec2 wall)
{
	float	dist_x;
	float	dist_y;
	float	dist;

	dist_x = fabs(wall.x - origin.x);
	dist_y = fabs(wall.y - origin.y);
	dist = sqrt(dist_x * dist_x + dist_y * dist_y);
	return (dist);
}

t_vec2	cast_ray_to_wall(t_vec2 origin, float angle, t_map *map)
{
	t_vec2	ray_coords;
	t_vec2	unit_vector;

	ray_coords = origin;
	unit_vector = normilize(angle);
	while (42)
	{
		ray_coords = cast_ray_to_border(ray_coords, angle);
		if (is_wall(ray_coords, unit_vector, map))
			return (ray_coords);
	}
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
