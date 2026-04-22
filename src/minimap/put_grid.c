/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 12:54:36 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/20 12:56:19 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static void	put_block_outline(mlx_image_t *minimap, t_render_obj outline);

void	put_grid(mlx_image_t *img, char **map_data, int bs)
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
