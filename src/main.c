/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:54:04 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/01 13:51:31 by dkalgano         ###   ########.fr       */
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

static void	update_window_info(mlx_t *mlx, int width, int height)
{
	if (width < DEFAULT_WIDTH)
		width = DEFAULT_WIDTH;
	if (height <= DEFAULT_HEIGHT)
		height = DEFAULT_HEIGHT;
	mlx->width = width;
	mlx->height = height;
}

static void	update_render_layour(t_render_layout *layout, t_map *map, int width, int height)
{
	if (width > MAX_WIDTH)
	{
		layout->game_width = MAX_WIDTH;
		layout->game_height = MAX_WIDTH / ((float)width / (float)height);
		layout->game_bs = get_block_size(map, layout->game_width, layout->game_height);
		layout->rescale = true;
	}
	else
	{
		layout->game_width = width;
		layout->game_height = height;
		layout->game_bs = get_block_size(map, width, height);
		layout->rescale = false;
	}
	layout->minimap_width = layout->game_width * 0.2f;
	layout->minimap_height = layout->game_height * 0.2f;
	layout->minimap_bs = get_block_size(map, layout->minimap_width, layout->minimap_height);
}

static void	on_resize(int32_t width, int32_t height, void *param)
{
	t_cub3d		*info;
	bool		reallocate;

	info = param;
	reallocate = width >= info->mlx->width;
	update_window_info(info->mlx, width, height);
	update_render_layour(&info->layout, &info->map, width, height);
	update_buffers(info, reallocate);
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
	mlx_scale_image_into(info->game, info->window);
}
