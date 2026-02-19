/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:54:04 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/19 16:29:16 by dkalgano         ###   ########.fr       */
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

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void on_resize(int32_t width, int32_t height, void *param)
{
	mlx_t*	mlx;

	mlx = param;
	mlx->width = width;
	mlx->height = height;
	printf("Window resized: %d x %d\n", width, height);
}

// -----------------------------------------------------------------------------

void	putmap();

int32_t	main(int argc, char **argv)
{
	mlx_t*		mlx;
	t_map		map;
	t_player	player;
	int			fd;

	if (argc != 2)
		return (EXIT_FAILURE);

	fd = open(argv[1], O_RDONLY);
	if (parse_map(fd, &map, &player) == false)
		return (EXIT_FAILURE);
1
	mlx = init_mlx();
	if (mlx == NULL)
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}

	printf("Current value of window: %d , %d\n", mlx->width, mlx->height);
	mlx_resize_hook(mlx, on_resize, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);

	return (EXIT_SUCCESS);
}

static mlx_t*	init_mlx(void)
{
	mlx_t*	created;

	mlx_set_setting(MLX_MAXIMIZED, true);
	created = mlx_init(512, 512, TITLE, true);
	return (created);
}
