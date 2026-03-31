/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_game_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:30:05 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/31 20:05:33 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		put_ceiling(t_cub3d *info, int x, int *y);
static void		put_floor(t_cub3d *info, int x, int *y);
static float	fog_factor(int row, int screen_h);
static uint32_t	foggy_rgba(uint8_t r, uint8_t g, uint8_t b,
					int row, int screen_h);

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

static float	fog_factor(int row, int screen_h)
{
	float	half_h;
	float	dist;
	float	t;

	half_h = (float)screen_h / 2.0f;
	/* dist = 0 at horizon (farthest), 1.0 at edges (closest) */
	dist = ((float)row - half_h) / half_h;
	if (dist < 0.0f)
		dist = -dist;
	/* t = 1.0 at horizon (far = dark), t = 0.0 at edges (close = bright) */
	t = 2.0f - dist;
	return (t * t);
}

static uint32_t	foggy_rgba(uint8_t r, uint8_t g, uint8_t b,
					int row, int screen_h)
{
	float	t;
	float	shade;

	t = fog_factor(row, screen_h);
	shade = 1.0f - (t * 0.15f);
	return (get_rgba(
			(uint8_t)((float)r * shade),
			(uint8_t)((float)g * shade),
			(uint8_t)((float)b * shade),
			255));
}

static void	put_ceiling(t_cub3d *info, int x, int *y)
{
	int	end;

	end = info->rays.top_borders[x];
	if (end < 0)
		end = 0;
	while (*y < end)
	{
		mlx_put_pixel(info->game, x, *y,
			foggy_rgba(
				info->textures.ceiling[0],
				info->textures.ceiling[1],
				info->textures.ceiling[2],
				*y,
				(int)info->game->height));
		(*y)++;
	}
}

static void	put_floor(t_cub3d *info, int x, int *y)
{
	while (*y < (int)info->game->height)
	{
		mlx_put_pixel(info->game, x, *y,
			foggy_rgba(
				info->textures.floor[0],
				info->textures.floor[1],
				info->textures.floor[2],
				*y,  /* ← this passes the correct row */
				(int)info->game->height));
		(*y)++;
	}
}
