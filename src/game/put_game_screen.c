/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_game_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:30:05 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/10 17:50:06 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	put_ceiling(mlx_image_t *img, t_textures *texts, t_icoords coords,
				int top_wall_border);
int			put_textures(mlx_image_t *img, t_rays *rays, t_png_textures *texts,
				t_icoords coords);
static void	put_floor(mlx_image_t *img, t_textures *texts, t_icoords coords);

void	put_game_screen(mlx_image_t *img, t_rays *rays, t_textures *texts,
			t_png_textures *pngs)
{
	t_icoords	coords;
	int			top_wall_border;

	coords.x = 0;
	while (coords.x < (int)rays->count)
	{
		coords.y = 0;
		top_wall_border = rays->top_borders[coords.x];
		coords.y = put_ceiling(img, texts, coords, top_wall_border);
		coords.y = put_textures(img, rays, pngs, coords);
		put_floor(img, texts, coords);
		coords.x++;
	}
}

static int	put_ceiling(mlx_image_t *img, t_textures *texts, t_icoords coords,
				int top_wall_border)
{
	uint32_t	pixel;

	if (top_wall_border < 0)
		top_wall_border = 0;
	while (coords.y < top_wall_border)
	{
		pixel = get_rgba(
				texts->ceiling[0],
				texts->ceiling[1],
				texts->ceiling[2],
				255);
		mlx_put_pixel(img, coords.x, coords.y, pixel);
		(coords.y)++;
	}
	return (coords.y);
}

static void	put_floor(mlx_image_t *img, t_textures *texts, t_icoords coords)
{
	uint32_t	pixel;

	while (coords.y < ((int)img->height - 1)
	{
		pixel = get_rgba(
				texts->floor[0],
				texts->floor[1],
				texts->floor[2],
				255);
		mlx_put_pixel(img, coords.x, coords.y, pixel);
		(coords.y)++;
	}
}
