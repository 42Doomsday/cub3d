/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:54:04 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/31 19:44:01 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>

#include "cub3d.h"

#define MAX_WIDTH 1024

static void	get_frame(void *param);
static void	on_resize(int32_t width, int32_t height, void *param);
static void	ft_hook(void *param);

int32_t	main(int argc, char **argv)
{
	t_cub3d	info;

	if (argc != 2)
		return (EXIT_FAILURE);

	if (init_info(&info, argv[1]) == false)
		return (EXIT_FAILURE);

	mlx_loop_hook(info.mlx, ft_hook, &info);
	mlx_resize_hook(info.mlx, on_resize, &info);
	mlx_loop_hook(info.mlx, get_frame, &info);
	mlx_loop(info.mlx);

	mlx_terminate(info.mlx);

	return (EXIT_SUCCESS);
}

static void	on_resize(int32_t width, int32_t height, void *param)
{
	t_cub3d		*info;
	int			org_height;
	int			org_width;
	bool		reallocate;

	printf("on resize\n");
	info = param;
	org_width = 0;
	org_height = 0;
	if (width < DEFAULT_WIDTH)
		width = DEFAULT_WIDTH;
	if (height <= DEFAULT_HEIGHT)
		height = DEFAULT_HEIGHT;
	else
	{
		if (info->mlx->width > MAX_WIDTH)
		{
			org_width = MAX_WIDTH;
			org_height = (float)(org_width) / ((float)width / (float)height);
			info->rescale = true;
		}
		else
			info->rescale = false;
	}
	reallocate = width >= info->mlx->width;
	info->mlx->width = width;
	info->mlx->height = height;
	update_info(info, org_width, org_height, reallocate);
}

static void	ft_hook(void *param)
{
	t_cub3d		*info;
	t_player	*player;

	info = param;
	player = &info->player;
	float dist = 5 * info->mlx->delta_time;
	if (dist > 1)
		return ;
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(info->mlx);
	else if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
	{
		update_player_degree(player, player->dir.degree - 100 * info->mlx->delta_time);
		precalculate_angles(&info->rays, player);
	}
	else if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
	{
		update_player_degree(player, player->dir.degree + 100 * info->mlx->delta_time);
		precalculate_angles(&info->rays, player);
	}
	else if (mlx_is_key_down(info->mlx, MLX_KEY_W))
		move_player(&info->map, &info->player, 90, dist);
	else if (mlx_is_key_down(info->mlx, MLX_KEY_S))
		move_player(&info->map, &info->player, 270, dist);
	else if (mlx_is_key_down(info->mlx, MLX_KEY_A))
		move_player(&info->map, &info->player, 0, dist);
	else if (mlx_is_key_down(info->mlx, MLX_KEY_D))
		move_player(&info->map, &info->player, 190, dist);
}

static void	get_frame(void *param)
{
	t_cub3d	*info;

	info = param;
	printf("fps: %f\n", 1 / (info->mlx->delta_time));
	get_all_rays(&info->rays, &info->map, &info->player, info->game->height);
	put_game_screen(info);
	put_minimap(info);
	if (info->rescale)
		mlx_scale_image_into(info->game, info->game_rescaled);
}
