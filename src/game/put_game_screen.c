/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_game_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:30:05 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/18 15:54:07 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_ceiling(t_textures *text, mlx_image_t *image, int x, int *y, int end);
static void put_textures(t_rays *rays, mlx_image_t *image, int x, int *y, int end);
static void	put_floor(t_textures *text, mlx_image_t *image, int x, int *y, int end);

void	put_game_screen(mlx_image_t *image, t_textures *text, t_rays *rays)
{
	size_t		x;
	int			y;
	float		proj_plane;
	int			wall_column_height;
	int			wall_top_px;
	int			wall_bot_px;

	proj_plane = (image->width / 2.0f) / tan(rays->fov / 2.0f);
	x = 0;
	while (x < rays->count)
	{
		y = 0;
		wall_column_height = (int)(proj_plane / rays->distances[x]);
		wall_top_px = (image->height / 2) - (wall_column_height / 2);
		wall_bot_px = (image->height / 2) + (wall_column_height / 2);
		if (wall_top_px < 0)
			wall_top_px = 0;
		if (wall_bot_px > (int)image->height)
			wall_bot_px = image->height;
		put_ceiling(text, image, x, &y, wall_top_px);
		put_textures(rays, image, x, &y, wall_bot_px);
		put_floor(text, image, x, &y, image->height);
		x++;
	}
}

static void	put_ceiling(t_textures *text, mlx_image_t *image, int x, int *y, int end)
{
	uint32_t	pixel;

	while (*y < end)
	{
		pixel = get_rgba(text->ceiling[0], text->ceiling[1], text->ceiling[2], 255);
		mlx_put_pixel(image, x, *y, pixel);
		(*y)++;
	}
}

static void	put_textures(t_rays *rays, mlx_image_t *image, int x, int *y, int end)
{
	uint32_t	texture[] = {
		get_rgba(255, 0, 0, 255),
		get_rgba(255, 165, 0, 255),
		get_rgba(255, 255, 0, 255),
		get_rgba(0, 128, 0, 255),
		get_rgba(0, 191, 255, 255),
		get_rgba(0, 0, 255, 255),
		get_rgba(128, 0, 128, 255)
	};
	size_t	text_size = 7;

	int	wall_width_in_px = image->width / rays->distances[x];
	int	one_pixel_on_texture = wall_width_in_px / text_size;
	int cur_pos_on_the_wall_in_px = get_cur_px_on_wall(rays->walls[x].coords, wall_width_in_px);
	uint32_t	pixel;

	pixel = texture[cur_pos_on_the_wall_in_px / one_pixel_on_texture];
	while (*y < end)
	{
		mlx_put_pixel(image, x, *y, pixel);
		(*y)++;
	}
}

static void	put_floor(t_textures *text, mlx_image_t *image, int x, int *y, int end)
{
	uint32_t	pixel;

	while (*y < end)
	{
		pixel = get_rgba(text->floor[0], text->floor[1], text->floor[2], 255);
		mlx_put_pixel(image, x, *y, pixel);
		(*y)++;
	}
}
