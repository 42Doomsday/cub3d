/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_game_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:30:05 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/20 15:46:46 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_ceiling(t_textures *text, mlx_image_t *image, int x, int *y, int end);
static void	put_textures(t_rays *rays, mlx_image_t *image, t_png_textures *pngs, int x, int *y, int end, int wall_top_px, int wall_column_hight);
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
		put_ceiling(text, image,  x, &y, wall_top_px);
		put_textures(rays, image, pngs, x, &y, wall_bot_px, wall_top_px, wall_column_height);
		put_floor(text, image, x, &y, image->height);
		x++;
	}
}

static void	put_ceiling(t_textures *text, mlx_image_t *image, int x, int *y, int end)
{
	uint32_t	pixel;
	int			protected_end;

	protected_end = end;
	if (end < 0)
		protected_end = 0;
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

static int	get_texture_column(t_wall_info *wall, mlx_texture_t *texture)
{
	int	column_idx;

	if (wall->side == NORTH || wall->side == SOUTH)
		column_idx = (int)((wall->coords.x - (float)(int)wall->coords.x) * (float)texture->width);
	else
		column_idx = (int)((wall->coords.y - (float)(int)wall->coords.y) * (float)texture->width);
	if (column_idx < 0)
		column_idx = 0;
	if (column_idx >= (int)texture->width)
		column_idx = (int)texture->width - 1;
	return (column_idx);
}

static int	put_to_limits(float text_pos, mlx_texture_t *texture)
{
	int	row_idx;

	row_idx = (int)text_pos;
	if (row_idx < 0)
		row_idx = 0;
	if (row_idx >= (int)texture->height)
		row_idx = (int)texture->height - 1;
	return (row_idx);
}

static void	put_textures(t_rays *rays, mlx_image_t *image, t_png_textures *pngs, int x, int *y, int end, int wall_top_px, int wall_column_hight)
{
	mlx_texture_t	*texture;
	uint32_t		pixel;
	int				text_x;
	int				text_y;
	float			step;
	float			text_pos;
	t_wall_info		*wall;
	int				protected_end;

	protected_end = end;
	if (end > (int)image->height)
		protected_end = image->height;
	wall = &rays->walls[x];
	texture = pngs->north;

	text_x = get_texture_column(wall, texture);
	step = (float)texture->height / (float)wall_column_hight;
	text_pos = (float)(*y - wall_top_px) * step;

	while (*y < protected_end)
	{
		text_y = put_to_limits(text_pos, texture);
		text_pos += step;
		pixel = get_text_pixel(texture, text_x, text_y);
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
