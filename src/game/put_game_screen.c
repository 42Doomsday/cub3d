/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_game_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:30:05 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/18 19:25:33 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_ceiling(t_textures *text, mlx_image_t *image, int x, int *y, int end);
static void	put_textures(t_rays *rays, mlx_image_t *image, t_png_textures *pngs, int x, int *y, int end);
static void	put_floor(t_textures *text, mlx_image_t *image, int x, int *y, int end);

void	put_game_screen(mlx_image_t *image, t_textures *text, t_png_textures *pngs, t_rays *rays)
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
		wall_column_height = roundf(proj_plane / rays->distances[x]);
		wall_top_px = (image->height / 2) - (wall_column_height / 2);
		wall_bot_px = (image->height / 2) + (wall_column_height / 2);
		if (wall_top_px < 0)
			wall_top_px = 0;
		if (wall_bot_px > (int)image->height)
			wall_bot_px = image->height;
		put_ceiling(text, image,  x, &y, wall_top_px);
		put_textures(rays, image, pngs, x, &y, wall_bot_px);
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

uint32_t get_text_pixel(mlx_texture_t *text, int x, int y)
{
	int	x_in_text_pixels = x * 4;
	int	offset_y = text->width * 4;
	int index = (offset_y * y) + x_in_text_pixels;

	uint8_t r = text->pixels[index + 0];
	uint8_t g = text->pixels[index + 1];
	uint8_t b = text->pixels[index + 2];
	uint8_t a = text->pixels[index + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	put_textures(t_rays *rays, mlx_image_t *image, t_png_textures *pngs, int x, int *y, int end)
{
	/* float	wall_height = end - *y; */
	float	wall_width_in_px = image->width / rays->distances[x];
	float	one_pixel_on_texture = wall_width_in_px / pngs->north->width;
	float	cur_pos_on_the_wall_in_px = get_cur_px_on_wall(rays->walls[x], wall_width_in_px);
	uint32_t	pixel;
	/* float step = (float)pngs->north->height / wall_height;
	float text_pos = (*y - image->height / 2 + wall_height) * step; */
	/* printf("width %d, height: %d\n", pngs->north->width, pngs->north->height);
	printf("wall_width_in_px = %f   wall_height %f\n", wall_width_in_px, wall_height); */
/* 	printf("step %f   text pos %f\n", step, text_pos); */
	/* printf("one_pixel_on_texture = %f\n", one_pixel_on_texture);
	printf("cur_pos_on_wall = %f\n", cur_pos_on_the_wall_in_px);
	printf("accessing pixel = %d\n", (int)(cur_pos_on_the_wall_in_px / one_pixel_on_texture)); */
	int i = 0;
	while (*y < end)
	{
/* 		int text_y = (int)text_pos;
		text_pos += step; */
		pixel = get_text_pixel(pngs->north, (int)(cur_pos_on_the_wall_in_px / one_pixel_on_texture), (int) i / one_pixel_on_texture);
		mlx_put_pixel(image, x, *y, pixel);
		(*y)++;
		i++;
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
