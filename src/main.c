/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:54:04 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/11 15:43:05 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cub3d.h"

#define DEFAULT_WIDTH 512
#define DEFAULT_HEIGHT 512
#define MINIMAP_PROCENT_SIZE 0.2f
#define TITLE "cub3d"

static mlx_t*	init_mlx(void);

void	update_mlx_size(t_cub3d *info, int32_t width, int32_t height)
{
	info->mlx->width = width;
	info->mlx->height = height;
}

void	put_minimap_image(t_cub3d *info)
{
	int32_t	width;
	int32_t	height;
	int32_t	margin;

	width = info->mlx->width * MINIMAP_PROCENT_SIZE;
	height = info->mlx->height * MINIMAP_PROCENT_SIZE;
	margin = width * MINIMAP_PROCENT_SIZE * MINIMAP_PROCENT_SIZE;
	info->minimap = mlx_new_image(info->mlx, width, height);
	info->minimap_bs = get_block_size(&info->map, width, height);
	put_minimap(info);
	mlx_image_to_window(info->mlx, info->minimap, margin, margin);
}

void	put_game_image(t_cub3d *info)
{
	int32_t	width;
	int32_t	height;

	width = info->mlx->width;
	height = info->mlx->height;
	info->game = mlx_new_image(info->mlx, width, height);
	info->game_bs = get_block_size(&info->map, width, height);
	put_game_screen(info->game, &info->map, &info->player);
	mlx_image_to_window(info->mlx, info->game, 0, 0);
}

void on_resize(int32_t width, int32_t height, void *param)
{
	t_cub3d*	info;

	info = param;
	update_mlx_size(info, width, height);
	printf("Window resized: %d x %d\n", width, height);

	mlx_delete_image(info->mlx, info->game);
	put_game_image(info);

	mlx_delete_image(info->mlx, info->minimap);
	put_minimap_image(info);
}

void ft_hook(void* param)
{
	t_cub3d*	info;

	info = param;
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(info->mlx);
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
		info->player.dir -= PLAYER_ROT_STEP;
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
		info->player.dir += PLAYER_ROT_STEP;
	if (mlx_is_key_down(info->mlx, MLX_KEY_W))
		move_player_forward(&info->map, &info->player);
	put_game_screen(info->game, &info->map, &info->player);
	put_minimap(info);
}

int32_t	main(int argc, char **argv)
{
	static t_cub3d	info;

	if (argc != 2)
		return (EXIT_FAILURE);

	if (parse(argv[1], &info) == false)
		return (EXIT_FAILURE);

	info.mlx = init_mlx();
	if (info.mlx == NULL)
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}

	put_game_image(&info);
	put_minimap_image(&info);

	mlx_loop_hook(info.mlx, ft_hook, &info);
	mlx_resize_hook(info.mlx, on_resize, &info);
	mlx_loop(info.mlx);
	mlx_terminate(info.mlx);

	return (EXIT_SUCCESS);
}

static mlx_t*	init_mlx(void)
{
	mlx_t*	created;

	mlx_set_setting(MLX_MAXIMIZED, true);
	created = mlx_init(512, 512, TITLE, true);
	return (created);
}
