/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:30:05 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/16 16:35:38 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_game_screen(mlx_image_t *image, t_rays *rays)
{
	size_t	i;
	float	proj_plane;

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
			mlx_put_pixel(image, i, j, get_rgba(30, 30, 30, 255));
			j++;
		}
		while (j < bot)
		{
			mlx_put_pixel(image, i, j, get_rgba(180, 100, 60, 255));
			j++;
		}
		while (j < (int)image->height)
		{
			mlx_put_pixel(image, i, j, get_rgba(80, 60, 40, 255));
			j++;
		}
		i++;
	}
}
