/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:13:33 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/01 13:47:51 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static void	put_grid(t_cub3d *info);
static void	put_square(mlx_image_t *minimap, int x, int y, int size, uint32_t pixel);
static void	put_block_outline(mlx_image_t *minimap, int x, int y, int size, uint32_t color);
static void	put_grid(t_cub3d *info);
static void	put_map(t_cub3d *info);

/* static void	fill_with_color(mlx_image_t *game)
{
	uint32_t	x;
	uint32_t	y;
	int			pixel;

	y = 0;
	pixel = get_rgba(255, 255, 255, 0);
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			mlx_put_pixel(game, x, y, pixel);
			x++;
		}
		y++;
	}
} */

void	put_minimap(t_cub3d *info)
{
	//fill_with_color(info->minimap);
	put_map(info);
	put_grid(info);
	put_player(info);
}

static void	put_map(t_cub3d *info)
{
	char **map;
	int	y;
	int	x;
	int	block;
	int32_t	pixel;

	map = info->map.data;
	block = info->layout.minimap_bs;
	y = 0;
	while (map && map[y])
	{
		x = 0;
		while (map[y][x])
		{
			pixel = get_rgba(50, 50, 50, 255);
			if (map[y][x] == '1')
				pixel = get_rgba(100, 100, 100, 255);
			else if (map[y][x] == '0')
				pixel = get_rgba(255, 255, 255, 255);
			put_square(info->game, x * block, y * block, block, pixel);
			x++;
		}
		y++;
	}
}

static void	put_grid(t_cub3d *info)
{
	char	**map;
	int		block;
	int		x;
	int		y;

	block = info->layout.minimap_bs;
	map = info->map.data;
	y = 0;
	while (map && map[y])
	{
		x = 0;
		while (map[y][x])
		{
			put_block_outline(
				info->game,
				x * block,
				y * block,
				block,
				get_rgba(33, 33, 33, 255)
			);
			x++;
		}
		y++;
	}
}

static void	put_square(mlx_image_t *minimap, int x, int y, int size, uint32_t pixel)
{
	int	i;
	int	j;

	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			mlx_put_pixel(minimap, x + i, y + j, pixel);
			i++;
		}
		j++;
	}
}

static void	put_block_outline(mlx_image_t *minimap, int x, int y, int size, uint32_t color)
{
	int thickness;
	int i;
	int t;

	thickness = size / 64;
	i = 0;
	while (i < size)
	{
		t = 0;
		while (t < thickness)
		{
			mlx_put_pixel(minimap, x + i, y + t, color);
			mlx_put_pixel(minimap, x + i, y + size - 1 - t, color);
			mlx_put_pixel(minimap, x + t, y + i, color);
			mlx_put_pixel(minimap, x + size - 1 - t, y + i, color);
			t++;
		}
		i++;
	}
}
