/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:13:33 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/07 16:08:50 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static void	put_block_outline(mlx_image_t *minimap, t_render_obj outline);
static void	put_grid(mlx_image_t *img, char **map_data, int bs);
static void	put_map(mlx_image_t *img, char **map_data, int bs);

void	put_minimap(mlx_image_t *img, t_world *world, t_rays *rays, int bs)
{
	put_map(img, world->map->data, bs);
	put_grid(img, world->map->data, bs);
	put_player(img, world->player, rays, bs);
}

static t_render_obj	get_square(int x, int y, int size, int32_t pixel)
{
	t_render_obj	square;

	square.x = x;
	square.y = y;
	square.size = size;
	square.colour = pixel;
	return (square);
}

static void	put_map(mlx_image_t *img, char **map_data, int bs)
{
	int				x;
	int				y;
	int32_t			pixel;
	t_render_obj	square;

	y = 0;
	while (map_data && map_data[y])
	{
		x = 0;
		while (map_data[y][x])
		{
			pixel = get_rgba(50, 50, 50, 255);
			if (map_data[y][x] == '1')
				pixel = get_rgba(100, 100, 100, 255);
			else if (map_data[y][x] == '0')
				pixel = get_rgba(255, 255, 255, 255);
			square = get_square(x * bs, y * bs, bs, pixel);
			put_square(img, square);
			x++;
		}
		y++;
	}
}

static void	put_grid(mlx_image_t *img, char **map_data, int bs)
{
	t_render_obj	outline;
	int				x;
	int				y;

	y = 0;
	while (map_data && map_data[y])
	{
		x = 0;
		while (map_data[y][x])
		{
			outline.x = x * bs;
			outline.y = y * bs;
			outline.size = bs;
			outline.colour = get_rgba(33, 33, 33, 255);
			put_block_outline(img, outline);
			x++;
		}
		y++;
	}
}

static void	put_block_outline(mlx_image_t *minimap, t_render_obj outline)
{
	int	thickness;
	int	x;
	int	y;
	int	i;
	int	t;

	x = outline.x;
	y = outline.y;
	thickness = outline.size / 64;
	i = 0;
	while (i < outline.size)
	{
		t = 0;
		while (t < thickness)
		{
			mlx_put_pixel(minimap, x + i, y + t, outline.colour);
			mlx_put_pixel(minimap, x + i, y + outline.size - 1 - t,
				outline.colour);
			mlx_put_pixel(minimap, x + t, y + i, outline.colour);
			mlx_put_pixel(minimap, x + outline.size - 1 - t, y + i,
				outline.colour);
			t++;
		}
		i++;
	}
}
