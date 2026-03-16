/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:30:05 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/16 16:00:18 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_all_rays(float *array, size_t size, t_map *map, t_player *player, float fov);
static void	build_walls(mlx_image_t *image, float *rays, size_t size, float fov);


void	put_game_screen(mlx_image_t *img, t_map *map, t_player *player)
{
	float	rays_arr[img->width];
	float	fov;

	fov = 90.0f * M_PI / 180.0f;
	get_all_rays(rays_arr, img->width, map,  player, fov);
	build_walls(img, rays_arr, img->width, fov);
}

static void	get_all_rays(float *array, size_t size, t_map *map, t_player *player, float fov)
{
	size_t	i;
	float	proj_plane_dist;
	float	offset;
	float	cur_angle;

	proj_plane_dist = (size / 2.0f) / tan(fov / 2.0f);
	i = 0;
	while (i < size)
	{
		offset = (size - i) - (size / 2.0f) + 0.5f;
		cur_angle = player->dir.radians + atan2f(offset, proj_plane_dist);
		array[i] = get_dist_to_wall(player->coords, cur_angle, map);
		array[i] *= cosf(cur_angle - player->dir.radians);
		i++;
	}
}

static void	build_walls(mlx_image_t *image, float *rays, size_t size, float fov)
{
	size_t	i;
	float	proj_plane;

	proj_plane = (image->width / 2.0f) / tan(fov / 2.0f);
	i = 0;
	while (i < size)
	{
		int col_height = (int)(proj_plane / rays[i]);
		int top = (image->height / 2) - (col_height / 2);
		int bot = (image->height / 2) + (col_height / 2);
		if (top < 0) top = 0;
		if (bot > (int)image->height)bot = image->height;
		int j = 0;
		while (j < top)
		{
			mlx_put_pixel(image, i, j, get_rgba(30, 30, 30, 255));
			j++;
		}
		while (j < bot)
		{
			mlx_put_pixel(image, i, j, get_rgba(180, 100, 60, 255));
			j++;
		}
		while (j < (int)image->height)
		{
			mlx_put_pixel(image, i, j, get_rgba(80, 60, 40, 255));
			j++;
		}
		i++;
	}
}
