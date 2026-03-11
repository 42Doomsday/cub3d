/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:54:04 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/11 13:16:14 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cub3d.h"

#define DEFAULT_WIDTH 512
#define DEFAULT_HEIGHT 512
#define TITLE "cub3d"

static mlx_t*	init_mlx(void);


void on_resize(int32_t width, int32_t height, void *param)
{
	t_cub3d*	info;

	info = param;
	info->mlx->width = width;
	info->mlx->height = height;
	printf("Window resized: %d x %d\n", width, height);
	mlx_delete_image(info->mlx, info->minimap);
	mlx_delete_image(info->mlx, info->game);
	info->minimap = mlx_new_image(info->mlx, info->mlx->width * 0.2f, info->mlx->height * 0.2f);
	info->game = mlx_new_image(info->mlx, info->mlx->width, info->mlx->height);
	put_game_screen(info->game, &info->map, &info->player);
	put_minimap(info);
	mlx_image_to_window(info->mlx, info->game, 0, 0);
	mlx_image_to_window(info->mlx, info->minimap, 0, 0);
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

	info.minimap = mlx_new_image(info.mlx, info.mlx->width * 0.2f, info.mlx->height * 0.2f);
	info.game = mlx_new_image(info.mlx, info.mlx->width, info.mlx->height);

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
