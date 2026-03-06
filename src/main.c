/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:54:04 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/06 13:51:56 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cub3d.h"

#define DEFAULT_WIDTH 512
#define DEFAULT_HEIGHT 512
#define TITLE "cub3d"

static mlx_image_t*	image;
static mlx_t*		init_mlx(void);
static t_cub3d		info;

int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_block_size(t_map *map, int32_t width, int32_t height)
{
	int	size1;
	int	size2;

	size1 = width / map->width;
	size2 = height / map->height;
	if (size1 < size2)
		return (size1);
	return (size2);
}

void	put_square(int x, int y, int size, uint32_t pixel)
{
	int	i;
	int	j;

	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			mlx_put_pixel(image, x + i, y + j, pixel);
			i++;
		}
		j++;
	}
}

void	put_map(t_map *map)
{
	char **maap;
	int	y;
	int	x;
	int	block;
	int32_t	pixel;

	maap = map->data;
	y = 0;
	block = get_block_size(map, image->width, image->height);
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
			put_square(x * block, y * block, block, pixel);
			x++;
		}
		y++;
	}
}

void	put_block_outline(int x, int y, int size, uint32_t color)
{
	int	i;

	i = 0;
	while (i < size)
	{
		mlx_put_pixel(image, x + i, y, color);
		mlx_put_pixel(image, x + i, y + size - 1, color);
		mlx_put_pixel(image, x, y + i, color);
		mlx_put_pixel(image, x + size - 1, y + i, color);
		i++;
	}
}

void	put_grid(t_map *map)
{
	int		x, y;
	char	**maap;
	int		block;

	block = get_block_size(map, image->width, image->height);
	maap = map->data;

	y = 0;
	while (maap && maap[y])
	{
		x = 0;
		while (maap[y][x])
		{
			put_block_outline(
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

void put_player(t_map *map, t_player *player)
{
    int block = get_block_size(map, image->width, image->height);

    int cx = (int)(player->x * block) + block / 2;
    int cy = (int)(player->y * block) + block / 2;

    int radius = block / 4;
    int x, y;

    float angle = (90.0f - player->rotation) * M_PI / 180.0f;

    for (y = -radius; y <= radius; y++)
        for (x = -radius; x <= radius; x++)
            if (x*x + y*y <= radius*radius)
                mlx_put_pixel(image, cx + x, cy + y, get_rgba(0, 255, 0, 255));

    int line_length = block / 2;
    int thickness = block / 20;

    for (int i = 0; i <= line_length; i++)
    {
        float px = (radius + i) * cos(angle);
        float py = -(radius + i) * sin(angle);

        for (int ty = -thickness/2; ty <= thickness/2; ty++)
            for (int tx = -thickness/2; tx <= thickness/2; tx++)
                mlx_put_pixel(image,
                              cx + (int)(px + 0.5f) + tx,
                              cy + (int)(py + 0.5f) + ty,
                              get_rgba(255, 0, 0, 255));
    }
}

void on_resize(int32_t width, int32_t height, void *param)
{
	mlx_t*	mlx;

	mlx = param;
	mlx->width = width;
	mlx->height = height;
	printf("Window resized: %d x %d\n", width, height);
	mlx_delete_image(info.mlx, image);
	image = mlx_new_image(info.mlx, info.mlx->width, info.mlx->height);
	put_map(&info.map);
	put_grid(&info.map);
	put_player(&info.map, &info.player);
	mlx_image_to_window(info.mlx, image, 0, 0);
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		info.player.rotation += PLAYER_ROT_STEP;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		info.player.rotation -= PLAYER_ROT_STEP;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move_player_forward(&info.map, &info.player);
	put_map(&info.map);
	put_grid(&info.map);
	put_player(&info.map, &info.player);
}

int32_t	main(int argc, char **argv)
{

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

	image = mlx_new_image(info.mlx, info.mlx->width, info.mlx->height);
	put_map(&info.map);
	put_player(&info.map, &info.player);
	mlx_image_to_window(info.mlx, image, 0, 0);

	mlx_loop_hook(info.mlx, ft_hook, info.mlx);
	mlx_resize_hook(info.mlx, on_resize, info.mlx);
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
