/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_game_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:30:05 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/16 18:36:10 by dkalgano         ###   ########.fr       */
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
			mlx_put_pixel(image, i, j, get_rgba(180, 100, 60, 255));
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
