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

bool    is_wall(t_vec2 coords, t_vec2 unit_vector, t_map *map);
float	find_dist(t_vec2 origin, t_vec2 unit_vector, bool coord);
t_vec2	normilize(float angle);

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

bool    is_wall(t_vec2 coords, t_vec2 unit_vector, t_map *map)
{
    int     x;
    int     y;
    bool    on_x_border;
    bool    on_y_border;

    on_x_border = fabs(coords.x - round(coords.x)) < 1e-5;
    on_y_border = fabs(coords.y - round(coords.y)) < 1e-5;

    if (on_x_border && unit_vector.x < 0)
        x = (int)floor(coords.x) - 1;
    else
        x = (int)floor(coords.x);

    if (on_y_border && unit_vector.y < 0)
        y = (int)floor(coords.y) - 1;
    else
        y = (int)floor(coords.y);

    // Защита от выхода за пределы карты
    if (x < 0 || y < 0 || y >= map->height || x >= map->width)
        return (true);

    if (on_x_border && on_y_border)
	{
		int x2 = (unit_vector.x < 0) ? (int)floor(coords.x) - 1 : (int)floor(coords.x);
		int y2 = (unit_vector.y < 0) ? (int)floor(coords.y) - 1 : (int)floor(coords.y);
		int x_neighbor = (int)floor(coords.x); // клетка по оси X
		int y_neighbor = (int)floor(coords.y); // клетка по оси Y

		// Проверяем обе смежные клетки (не диагональную)
		if (x_neighbor >= 0 && x_neighbor < map->width
			&& y2 >= 0 && y2 < map->height)
			if (map->data[y2][x_neighbor] == '1' || map->data[y2][x_neighbor] == ' ')
				return (true);
		if (x2 >= 0 && x2 < map->width
			&& y_neighbor >= 0 && y_neighbor < map->height)
			if (map->data[y_neighbor][x2] == '1' || map->data[y_neighbor][x2] == ' ')
				return (true);
	}
    return (map->data[y][x] == '1' || map->data[y][x] == ' ');
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
