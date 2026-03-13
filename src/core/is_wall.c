/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 14:06:28 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/13 14:13:08 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_vec2	is_on_edges(t_vec2 coords);
static int		get_block_coord(bool on_edge, float current, float unit_value);

bool	is_wall(t_vec2 start, t_vec2 unit_vector, t_map *map)
{
	t_vec2	on_edges;
	int		x;
	int		y;

	x = floor(start.x);
	y = floor(start.y);
	if (x > 0 && y > 0)
	{
		on_edges = is_on_edges(start);
		if (on_edges.x && on_edges.y)
		{
			x -= 1;
			y -= 1;
		}
		else if (on_edges.x || on_edges.y)
		{
			x = get_block_coord(on_edges.x, start.x, unit_vector.x);
			y = get_block_coord(on_edges.y, start.y, unit_vector.y);
		}
	}
	return (is_wall_or_space_on_coords(map, x, y));
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

static t_vec2	is_on_edges(t_vec2 coords)
{
	t_vec2	result;

	result.x = fabs(coords.x - round(coords.x)) < __FLT_EPSILON__;
	result.y = fabs(coords.y - round(coords.y)) < __FLT_EPSILON__;
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
