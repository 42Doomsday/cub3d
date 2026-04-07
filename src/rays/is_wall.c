/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 14:06:28 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/20 16:34:18 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	is_on_edges(t_coords coords, bool *cross_x, bool *cross_y);
static int	get_block_coord(bool on_edge, float current, float unit_value);

bool	is_wall(t_coords start, t_vec2 unit_vector, t_map *map)
{
	bool	is_on_x;
	bool	is_on_y;
	int		x;
	int		y;

	x = floor(start.x);
	y = floor(start.y);
	if (x > 0 && y > 0)
	{
		is_on_edges(start, &is_on_x, &is_on_y);
		if (is_on_x && is_on_y)
		{
			if (is_wall_or_space_on_coords(map, x - 1, y - 1))
				return (true);
		}
		else if (is_on_x || is_on_y)
		{
			x = get_block_coord(is_on_x, start.x, unit_vector.x);
			y = get_block_coord(is_on_y, start.y, unit_vector.y);
		}
	}
	return (is_wall_or_space_on_coords(map, x, y));
}

t_texture_id	get_side_of_wall(t_coords wall, t_vec2 unit_vector)
{
	bool			is_on_x;
	bool			is_on_y;
	t_texture_id	result;

	is_on_edges(wall, &is_on_x, &is_on_y);
	result = FLOOR;
	if (is_on_y)
	{
		if (unit_vector.y < 0)
			result = NORTH;
		else
			result = SOUTH;
	}
	else if (is_on_x)
	{
		if (unit_vector.x < 0)
			result = WEST;
		else
			result = EAST;
	}
	return (result);
}

bool	is_wall_or_space_on_coords(t_map *map, int x, int y)
{
	char	block_value;

	if (x < 0 || x >= map->width)
		return (true);
	if (y < 0 || y >= map->height)
		return (true);
	block_value = map->data[y][x];
	if (block_value == '1' || block_value == ' ')
		return (true);
	return (false);
}

static void	is_on_edges(t_coords coords, bool *cross_x, bool *cross_y)
{
	*cross_x = fabs(coords.x - round(coords.x)) < __FLT_EPSILON__;
	*cross_y = fabs(coords.y - round(coords.y)) < __FLT_EPSILON__;
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
