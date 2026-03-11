/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:13:33 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/11 13:17:18 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_grid(t_cub3d *info);
static void	put_square(mlx_image_t *minimap, int x, int y, int size, uint32_t pixel);
static void	put_block_outline(mlx_image_t *minimap, int x, int y, int size, uint32_t color);
static void	put_grid(t_cub3d *info);
static void	put_map(t_cub3d *info);

void	put_minimap(t_cub3d *info)
{
	put_map(info);
	put_grid(info);
	put_player(info->minimap, &info->map, &info->player);
}

static void	put_map(t_cub3d *info)
{
	char **maap;
	int	y;
	int	x;
	int	block;
	int32_t	pixel;

	maap = info->map.data;
	y = 0;
	block = get_block_size(&info->map, info->minimap->width, info->minimap->height);
	while (maap && maap[y])
	{
		x = 0;
		while (maap[y][x])
		{
			pixel = get_rgba(50, 50, 50, 255);
			if (maap[y][x] == '1')
				pixel = get_rgba(100, 100, 100, 255);
			else if (maap[y][x] == '0')
				pixel = get_rgba(255, 255, 255, 255);
			put_square(info->minimap, x * block, y * block, block, pixel);
			x++;
		}
		y++;
	}
}

static void	put_grid(t_cub3d *info)
{
	int		x, y;
	char	**maap;
	int		block;

	block = get_block_size(&info->map, info->minimap->width, info->minimap->height);
	maap = info->map.data;

	y = 0;
	while (maap && maap[y])
	{
		x = 0;
		while (maap[y][x])
		{
			put_block_outline(
				info->minimap,
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
	if (thickness < 1)
		thickness = 1;
	i = 0;
	while (i < size)
	{
		t = 0;
		while (t < thickness)
		{
			mlx_put_pixel(minimap, x + i, y + t, color);           // верх
			mlx_put_pixel(minimap, x + i, y + size - 1 - t, color); // низ
			mlx_put_pixel(minimap, x + t, y + i, color);           // лево
			mlx_put_pixel(minimap, x + size - 1 - t, y + i, color); // право
			t++;
		}
		i++;
	}
}
