/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_game_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:30:05 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/20 17:44:41 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_ceiling(t_textures *text, mlx_image_t *image, t_rays *rays, int x, int *y);
static void	put_textures(t_png_textures *pngs, mlx_image_t *image, t_rays *rays, int x, int *y);
static void	put_floor(t_textures *text, mlx_image_t *image, int x, int *y, int end);

void	put_game_screen(mlx_image_t *image, t_textures *text, t_png_textures *pngs, t_rays *rays)
{
	size_t	x;
	int		y;

	x = 0;
	while (x < rays->count)
	{
		y = 0;
		put_ceiling(text, image, rays, x, &y);
		put_textures(pngs, image, rays, x, &y);
		put_floor(text, image, x, &y, image->height);
		x++;
	}
}

static void	put_ceiling(t_textures *text, mlx_image_t *image, t_rays *rays, int x, int *y)
{
	uint32_t	pixel;
	int			end;

	end = rays->top_borders[x];
	if (end < 0)
		end = 0;
	while (*y < end)
	{
		pixel = get_rgba(
			text->ceiling[0],
			text->ceiling[1],
			text->ceiling[2],
			255
		);
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

static int	get_texture_column(t_texture_id side, t_coords coords, mlx_texture_t *texture)
{
	int	column_idx;

	if (side == NORTH || side == SOUTH)
		column_idx = (int)((coords.x - (float)(int)coords.x) * (float)texture->width);
	else
		column_idx = (int)((coords.y - (float)(int)coords.y) * (float)texture->width);
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

static void	put_textures(t_png_textures *pngs, mlx_image_t *image, t_rays *rays, int x, int *y)
{
	mlx_texture_t	*texture;
	uint32_t		pixel;
	int				text_x;
	int				text_y;
	float			step;
	float			text_pos;
	int				protected_end;

	protected_end = rays->bot_borders[x];
	if (rays->bot_borders[x] > (int)image->height)
		protected_end = image->height;

	texture = pngs->north;

	text_x = get_texture_column(rays->sides[x], rays->coords[x], texture);
	step = (float)texture->height / (float)rays->heights[x];
	text_pos = (float)(*y - rays->top_borders[x]) * step;

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
