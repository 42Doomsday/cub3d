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

static t_vec2	get_ray_dir(float angle);
static float	dist_to_vertical_edge(t_vec2 origin, t_vec2 ray_dir);
static float	dist_to_horizontal_edge(t_vec2 origin, t_vec2 ray_dir);

/**
 * @brief Finds the first grid boundary crossing from @p origin along
 *        @p angle, staying within the current tile.
 *
 * Computes the distance to the nearest vertical grid line and the nearest
 * horizontal grid line separately, then returns the intersection point of
 * whichever is closer.
 *
 * @param origin  Ray origin in world-space tile coordinates.
 * @param angle   Ray direction in radians (standard math convention).
 * @return        World-space coordinates of the first tile edge crossing.
 */
t_vec2	cast_ray_to_wall(t_vec2 origin, float angle)
{
	t_vec2	ray_dir;
	float	dist_x;
	float	dist_y;

	ray_dir = get_ray_dir(angle);
	dist_x = dist_to_vertical_edge(origin, ray_dir);
	dist_y = dist_to_horizontal_edge(origin, ray_dir);
	if (dist_x < dist_y)
		return ((t_vec2){origin.x + ray_dir.x * dist_x,
			origin.y + ray_dir.y * dist_x});
	return ((t_vec2){origin.x + ray_dir.x * dist_y,
		origin.y + ray_dir.y * dist_y});
}

/**
 * @brief Returns both tile edge crossings: vertical and horizontal.
 *
 * Instead of picking the closer one, both intersection points are written
 * into @p out so the caller can draw both rays independently.
 *
 * @param origin  Ray origin in world-space tile coordinates.
 * @param angle   Ray direction in radians (standard math convention).
 * @param out     Output array of exactly two t_vec2: [0] = vertical edge
 *                crossing, [1] = horizontal edge crossing.
 */
void	cast_ray_both_edges(t_vec2 origin, float angle, t_vec2 out[2])
{
	t_vec2	ray_dir;
	float	dist_x;
	float	dist_y;

	ray_dir = get_ray_dir(angle);
	dist_x = dist_to_vertical_edge(origin, ray_dir);
	dist_y = dist_to_horizontal_edge(origin, ray_dir);
	printf("Ray - x:%f y:%f\n", ray_dir.x, ray_dir.y);
	printf("DistX - %f\n", dist_x);
	printf("DistY - %f\n", dist_y);
	out[0].x = origin.x + ray_dir.x * dist_x;
	out[0].y = origin.y + ray_dir.y * dist_x;
	out[1].x = origin.x + ray_dir.x * dist_y;
	out[1].y = origin.y + ray_dir.y * dist_y;
}

/**
 * @brief Builds a unit direction vector from a radian angle.
 *
 * @param angle  Ray angle in radians (standard math convention).
 * @return       Normalised direction vector.
 */
static t_vec2	get_ray_dir(float angle)
{
	t_vec2	ray_dir;

	ray_dir.x = cosf(angle);
	ray_dir.y = -sinf(angle);
	return (ray_dir);
}

/**
 * @brief Computes the distance along the ray to the nearest vertical
 *        grid line (left or right edge of the current tile).
 *
 * @param origin   Ray origin in world-space tile coordinates.
 * @param ray_dir  Normalised ray direction vector.
 * @return         Distance to the nearest vertical tile edge.
 */
static float	dist_to_vertical_edge(t_vec2 origin, t_vec2 ray_dir)
{
	float	edge_x;

	if (ray_dir.x == 0)
		return (1e30f);
	if (ray_dir.x > 0)
		edge_x = floorf(origin.x) + 1.0f;
	else
		edge_x = floorf(origin.x);
	return ((edge_x - origin.x) / ray_dir.x);
}

/**
 * @brief Computes the distance along the ray to the nearest horizontal
 *        grid line (top or bottom edge of the current tile).
 *
 * @param origin   Ray origin in world-space tile coordinates.
 * @param ray_dir  Normalised ray direction vector.
 * @return         Distance to the nearest horizontal tile edge.
 */
static float	dist_to_horizontal_edge(t_vec2 origin, t_vec2 ray_dir)
{
	float	edge_y;

	if (ray_dir.y == 0)
		return (1e30f);
	if (ray_dir.y > 0)
		edge_y = floorf(origin.y) + 1.0f;
	else
		edge_y = floorf(origin.y);
	return ((edge_y - origin.y) / ray_dir.y);
}
