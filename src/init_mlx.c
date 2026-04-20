/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 12:17:23 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/20 13:12:18 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_t	*init_engine(t_cub3d *info);
static bool		setup_images(t_cub3d *info);

bool	init_mlx(t_cub3d *info)
{
	info->mlx = init_engine(info);
	if (info->mlx)
	{
		mlx_set_cursor_mode(info->mlx, MLX_MOUSE_HIDDEN);
		if (setup_images(info))
			return (true);
		mlx_terminate(info->mlx);
	}
	print_error("mlx", (char *)mlx_strerror(mlx_errno));
	return (false);
}

static mlx_t	*init_engine(t_cub3d *info)
{
	mlx_t	*mlx;

	mlx_set_setting(MLX_FULLSCREEN, info->fullscreen == true);
	mlx_set_setting(MLX_MAXIMIZED, info->fullscreen == false);
	if (info->fullscreen)
		mlx = mlx_init(FULLSCREEN_WIDTH, FULLSCREEN_HEIGHT, TITLE, true);
	else
		mlx = mlx_init(MIN_WIDTH, MIN_HEIGHT, TITLE, true);
	return (mlx);
}

static bool	setup_images(t_cub3d *info)
{
	info->game = mlx_new_image(info->mlx, info->mlx->width, info->mlx->height);
	if (info->game)
	{
		if (info->fullscreen)
		{
			if (mlx_image_to_window(info->mlx, info->game, 0, 0) != -1)
				return (true);
		}
		else
		{
			info->window = mlx_new_image(info->mlx, info->mlx->width,
					info->mlx->height);
			if (info->window)
			{
				if (mlx_image_to_window(info->mlx, info->window, 0, 0) != -1)
					return (true);
				mlx_delete_image(info->mlx, info->window);
			}
		}
		mlx_delete_image(info->mlx, info->game);
	}
	return (false);
}
