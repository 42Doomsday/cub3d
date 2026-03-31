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

static t_coords	cast_ray_to_border(t_coords origin, t_vec2 unit_vector);
static float	find_dist(t_coords origin, t_vec2 unit_vector, bool coord);

void	get_all_rays(t_rays *rays, t_map *map, t_player *player, int height)
{
	size_t	i;
	float	proj_plane_dist;

	proj_plane_dist = (rays->count / 2.0f) / tan(rays->fov / 2.0f);
	i = 0;
	while (i < rays->count)
	{
		rays->coords[i] = cast_ray_to_wall(player->coords, rays->norm_angles[i], map);
		rays->sides[i] = get_side_of_wall(rays->coords[i], rays->norm_angles[i]);
		rays->distances[i] = get_dist_to_wall(player->coords, rays->coords[i]);
		rays->distances[i] *= cosf(rays->angles[i] - player->dir.radians);
		rays->heights[i] =  roundf(proj_plane_dist / rays->distances[i]);
		rays->top_borders[i] = (height / 2) - (rays->heights[i] / 2);
		rays->bot_borders[i] = (height / 2) + (rays->heights[i] / 2);
		i++;
	}
}

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

t_coords	cast_ray_to_wall(t_coords origin, t_vec2 unit_vector, t_map *map)
{
	t_coords	ray_coords;

	ray_coords = origin;
	while (42)
	{
		ray_coords = cast_ray_to_border(ray_coords, unit_vector);
		if (is_wall(ray_coords, unit_vector, map))
			return (ray_coords);
	}
}

static t_coords	cast_ray_to_border(t_coords origin, t_vec2 unit_vector)
{
	t_coords	point;
	float		dist;
	float		dist_second;

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
	float	orig_val;
	float	unit_val;
	int		int_val;

	if (coord == 0)
	{
		orig_val = origin.x;
		unit_val = unit_vector.x;
	}
	else
	{
		orig_val = origin.y;
		unit_val = unit_vector.y;
	}
	if (unit_val == 0.0f)
		return (1e30f);
	int_val = (int)orig_val;
	if (unit_val > 0.0f)
		return (((float)int_val + 1.0f - orig_val) / unit_val);
	if ((float)int_val == orig_val)
		return (-1.0f / unit_val);
	return (((float)int_val - orig_val) / unit_val);
}
