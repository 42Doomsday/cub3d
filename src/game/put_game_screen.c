/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_game_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:30:05 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/31 17:55:43 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_ceiling(t_cub3d *info, int x, int *y);
static void	put_floor(t_cub3d *info, int x, int *y);

void	put_game_screen(t_cub3d *info)
{
	size_t	x;
	int		y;

	x = 0;
	while (x < info->rays.count)
	{
		y = 0;
		put_ceiling(info, x, &y);
		put_textures(info, x, &y);
		put_floor(info, x, &y);
		x++;
	}
}

static void	put_ceiling(t_cub3d *info, int x, int *y)
{
	uint32_t	pixel;
	int			end;

	end = info->rays.top_borders[x];
	if (end < 0)
		end = 0;
	while (*y < end)
	{
		pixel = get_rgba(
				info->textures.ceiling[0],
				info->textures.ceiling[1],
				info->textures.ceiling[2],
				255);
		mlx_put_pixel(info->game, x, *y, pixel);
		(*y)++;
	}
}

static void	put_floor(t_cub3d *info, int x, int *y)
{
	uint32_t	pixel;

	while (*y < (int)info->game->height)
	{
		pixel = get_rgba(
				info->textures.floor[0],
				info->textures.floor[1],
				info->textures.floor[2],
				255);
		mlx_put_pixel(info->game, x, *y, pixel);
		(*y)++;
	}
}
