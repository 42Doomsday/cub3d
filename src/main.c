/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:54:04 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/11 13:09:57 by dkalgano         ###   ########.fr       */
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

void	put_square(mlx_image_t *minimap, int x, int y, int size, uint32_t pixel)
{
	int	i;
	int	j;

	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			mlx_put_pixel(minimap, x + i, y + j, pixel);
			i++;
		}
		j++;
	}
}

void	put_map(t_cub3d *info)
{
	char **maap;
	int	y;
	int	x;
	int	block;
	int32_t	pixel;

	maap = info->map.data;
	y = 0;
	block = get_block_size(&info->map, info->minimap->width, info->minimap->height);
	while (maap && maap[y])
	{
		x = 0;
		while (maap[y][x])
		{
			pixel = get_rgba(50, 50, 50, 255);
			if (maap[y][x] == '1')
				pixel = get_rgba(100, 100, 100, 255);
			else if (maap[y][x] == '0')
				pixel = get_rgba(255, 255, 255, 255);
			put_square(info->minimap, x * block, y * block, block, pixel);
			x++;
		}
		y++;
	}
}

void    put_block_outline(mlx_image_t *minimap, int x, int y, int size, uint32_t color)
{
	int thickness;
	int i;
	int t;

	thickness = size / 64;
	if (thickness < 1)
		thickness = 1;
	i = 0;
	while (i < size)
	{
		t = 0;
		while (t < thickness)
		{
			mlx_put_pixel(minimap, x + i, y + t, color);           // верх
			mlx_put_pixel(minimap, x + i, y + size - 1 - t, color); // низ
			mlx_put_pixel(minimap, x + t, y + i, color);           // лево
			mlx_put_pixel(minimap, x + size - 1 - t, y + i, color); // право
			t++;
		}
		i++;
	}
}


void	put_grid(t_cub3d *info)
{
	int		x, y;
	char	**maap;
	int		block;

	block = get_block_size(&info->map, info->minimap->width, info->minimap->height);
	maap = info->map.data;

	y = 0;
	while (maap && maap[y])
	{
		x = 0;
		while (maap[y][x])
		{
			put_block_outline(
				info->minimap,
				x * block,
				y * block,
				block,
				get_rgba(33, 33, 33, 255)
			);
			x++;
		}
		y++;
	}
}

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
	put_map(info);
	put_grid(info);
	put_player(info->minimap, &info->map, &info->player);
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
	put_map(info);
	put_grid(info);
	put_player(info->minimap, &info->map, &info->player);
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
