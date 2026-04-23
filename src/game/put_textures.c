/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 19:43:59 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/23 15:31:18 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_texture_t	*get_text(t_texture_id side, t_png_textures *pngs);
static uint32_t			get_text_pixel(mlx_texture_t *text, int x, int y);
static int				get_text_clmn(t_texture_id side, t_coords crds,
							mlx_texture_t *text);
static int				put_to_limits(float value, int limit);

int	put_textures(mlx_image_t *img, t_rays *rays, t_png_textures *texts,
		t_icoords coords)
{
	mlx_texture_t	*texture;
	t_coords		text;
	float			step;
	float			text_pos_y;
	int				end;

	texture = get_text(rays->sides[coords.x], texts);
	text.x = get_text_clmn(rays->sides[coords.x],
			rays->coords[coords.x], texture);
	step = (float)texture->height / (float)rays->heights[coords.x];
	text_pos_y = (float)(coords.y - rays->top_borders[coords.x]) * step;
	end = put_to_limits(rays->bot_borders[coords.x], img->height);
	while (coords.y < end)
	{
		text.y = put_to_limits(text_pos_y, texture->height);
		text_pos_y += step;
		mlx_put_pixel(img, coords.x, coords.y,
			get_text_pixel(texture, text.x, text.y));
		(coords.y)++;
	}
	return (coords.y);
}

static mlx_texture_t	*get_text(t_texture_id side, t_png_textures *pngs)
{
	mlx_texture_t	*texture;

	texture = NULL;
	if (side == NORTH)
		texture = pngs->north;
	else if (side == EAST)
		texture = pngs->east;
	else if (side == WEST)
		texture = pngs->west;
	else if (side == SOUTH)
		texture = pngs->south;
	return (texture);
}

static uint32_t	get_text_pixel(mlx_texture_t *text, int x, int y)
{
	uint32_t	result;
	int			x_in_text_pixels;
	int			offset_y;
	int			index;

	x_in_text_pixels = x * 4;
	offset_y = text->width * 4;
	index = (offset_y * y) + x_in_text_pixels;
	result = text->pixels[index + 0] << 24;
	result |= text->pixels[index + 1] << 16;
	result |= text->pixels[index + 2] << 8;
	result |= text->pixels[index + 3];
	return (result);
}

static int	get_text_clmn(t_texture_id side, t_coords crds, mlx_texture_t *text)
{
	int	column_idx;

	if (side == NORTH)
		column_idx = (int)((crds.x - (float)(int)crds.x) * (float)text->width);
	else if (side == SOUTH)
		column_idx = (int)((ceilf(crds.x) - crds.x) * (float)text->width);
	else if (side == WEST)
		column_idx = (int)((ceilf(crds.y) - crds.y) * (float)text->width);
	else
		column_idx = (int)((crds.y - (float)(int)crds.y) * (float)text->width);
	if (column_idx < 0)
		column_idx = 0;
	if (column_idx >= (int)text->width)
		column_idx = (int)text->width - 1;
	return (column_idx);
}

static int	put_to_limits(float value, int limit)
{
	int	row_idx;

	row_idx = (int)value;
	if (row_idx < 0)
		row_idx = 0;
	if (row_idx >= limit)
		row_idx = limit - 1;
	return (row_idx);
}
