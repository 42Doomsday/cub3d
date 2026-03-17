/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_game_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:30:05 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/17 14:35:15 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_game_screen(mlx_image_t *image, t_textures *text, t_rays *rays)
{
	size_t	i;
	float	proj_plane;
	int		pixel;

	proj_plane = (image->width / 2.0f) / tan(rays->fov / 2.0f);
	i = 0;
	while (i < rays->count)
	{
		int col_height = (int)(proj_plane / rays->distances[i]);
		int top = (image->height / 2) - (col_height / 2);
		int bot = (image->height / 2) + (col_height / 2);
		if (top < 0) top = 0;
		if (bot > (int)image->height)bot = image->height;
		int j = 0;
		while (j < top)
		{
			pixel = get_rgba(text->ceiling[0], text->ceiling[1], text->ceiling[2], 255);
			mlx_put_pixel(image, i, j, pixel);
			j++;
		}
		while (j < bot)
		{
			if (rays->walls[i].side == NORTH)
				pixel = get_rgba(170, 90, 50, 255);
			else if (rays->walls[i].side == EAST)
				pixel = get_rgba(160, 80, 40, 255);
			else if (rays->walls[i].side == SOUTH)
				pixel = get_rgba(150, 70, 60, 255);
			else if (rays->walls[i].side == WEST)
				pixel = get_rgba(180, 100, 60, 255);
			mlx_put_pixel(image, i, j, pixel);
			j++;
		}
		while (j < (int)image->height)
		{
			pixel = get_rgba(text->floor[0], text->floor[1], text->floor[2], 255);
			mlx_put_pixel(image, i, j, pixel);
			j++;
		}
		i++;
	}
}
