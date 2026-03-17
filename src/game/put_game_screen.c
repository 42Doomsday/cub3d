/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_game_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:30:05 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/17 17:11:41 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_game_screen(mlx_image_t *image, t_textures *text, t_rays *rays)
{
	size_t		i;
	float		proj_plane;
	int			pixel;

	uint32_t	texture[] = {
		get_rgba(255, 0, 0, 255),
		get_rgba(255, 165, 0, 255),
		get_rgba(255, 255, 0, 255),
		get_rgba(0, 128, 0, 255),
		get_rgba(0, 191, 255, 255),
		get_rgba(0, 0, 255, 255),
		get_rgba(128, 0, 128, 255)
	};
	size_t	text_size = 7;

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
		/* printf("New game_bs is %d\n", info->game_bs);
	printf("First ray distance %f\n", info->rays.distances[0]);
	printf("1/distance=%f\n", 1 / info->rays.distances[0]);
	printf("wall_width_in_px=width/distance=%d\n", (int)(width / info->rays.distances[0]));
	printf("one_pixel_on_texture=wall_width_in_px/text_size=%d\n", (int)(width / info->rays.distances[0]) / 8); */
		int	wall_width_in_px = roundf(image->width / rays->distances[i]);
		int	one_pixel_on_texture = roundf(wall_width_in_px / text_size);
		int cur_pos_on_the_wall_in_px = get_cur_px_on_wall(rays->walls[i].coords, wall_width_in_px);
		printf("cur pos: %d\n", cur_pos_on_the_wall_in_px);
		printf("one_pixel_on_texture: %d\n", one_pixel_on_texture);
		pixel = texture[cur_pos_on_the_wall_in_px / one_pixel_on_texture];
		printf("division: %d\n", cur_pos_on_the_wall_in_px / one_pixel_on_texture);
		while (j < bot)
		{
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
