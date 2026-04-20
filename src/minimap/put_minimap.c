/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:13:33 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/20 13:13:29 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static void			put_floor_and_space(mlx_image_t *img, char **map_data,
						int bs);
static void			put_walls(mlx_image_t *img, char **map_data, int bs);
static t_render_obj	get_square(int x, int y, int size, int32_t pixel);

void	put_minimap(mlx_image_t *img, t_world *world, t_rays *rays, int bs)
{
	put_floor_and_space(img, world->map->data, bs);
	put_grid(img, world->map->data, bs);
	put_player(img, world->player, rays, bs);
	put_walls(img, world->map->data, bs);
}

static void	put_walls(mlx_image_t *img, char **map_data, int bs)
{
	int				x;
	int				y;
	int32_t			pixel;
	t_render_obj	square;

	y = 0;
	pixel = get_rgba(100, 100, 100, 255);
	while (map_data && map_data[y])
	{
		x = 0;
		while (map_data[y][x])
		{
			if (map_data[y][x] == '1')
			{
				square = get_square(x * bs, y * bs, bs, pixel);
				put_square(img, square);
			}
			x++;
		}
		y++;
	}
}

void	put_floor_and_space(mlx_image_t *img, char **map_data, int bs)
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
			if (map_data[y][x] == '0' || map_data[y][x] == '1')
			{
				if (map_data[y][x] == '0')
					pixel = get_rgba(255, 255, 255, 255);
				else
					pixel = get_rgba(50, 50, 50, 255);
				square = get_square(x * bs, y * bs, bs, pixel);
				put_square(img, square);
			}
			x++;
		}
		y++;
	}
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
