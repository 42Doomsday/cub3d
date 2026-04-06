/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:13:33 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/06 17:41:52 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static void	put_grid(t_cub3d *info);
static void	put_block_outline(mlx_image_t *minimap, t_render_obj outline);
static void	put_grid(t_cub3d *info);
static void	put_map(t_cub3d *info);

void	put_minimap(t_cub3d *info)
{
	put_map(info);
	put_grid(info);
	put_player(info);
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

static void	put_map(t_cub3d *info)
{
	int				x;
	int				y;
	int				block;
	int32_t			pixel;
	t_render_obj	square;

	block = info->layout->minimap_bs;
	y = 0;
	while (info->map->data && info->map->data[y])
	{
		x = 0;
		while (info->map->data[y][x])
		{
			pixel = get_rgba(50, 50, 50, 255);
			if (info->map->data[y][x] == '1')
				pixel = get_rgba(100, 100, 100, 255);
			else if (info->map->data[y][x] == '0')
				pixel = get_rgba(255, 255, 255, 255);
			square = get_square(x * block, y * block, block, pixel);
			put_square(info->game, square);
			x++;
		}
		y++;
	}
}

static void	put_grid(t_cub3d *info)
{
	t_render_obj	outline;
	char			**map;
	int				block;
	int				x;
	int				y;

	block = info->layout->minimap_bs;
	map = info->map->data;
	y = 0;
	while (map && map[y])
	{
		x = 0;
		while (map[y][x])
		{
			outline.x = x * block;
			outline.y = y * block;
			outline.size = block;
			outline.colour = get_rgba(33, 33, 33, 255);
			put_block_outline(info->game, outline);
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
