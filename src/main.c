/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:54:04 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/18 16:57:55 by dkalgano         ###   ########.fr       */
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

static void	put_minimap_image(t_cub3d *info);
static void	put_game_image(t_cub3d *info);
static void	on_resize(int32_t width, int32_t height, void *param);
static void	ft_hook(void *param);

void	get_all_rays(t_rays *rays, t_map *map, t_player *player)
{
	size_t	i;
	float	proj_plane_dist;
	float	offset;
	float	cur_angle;

	proj_plane_dist = (rays->count / 2.0f) / tan(rays->fov / 2.0f);
	i = 0;
	while (i < rays->count)
	{
		offset = (rays->count - i) - (rays->count / 2.0f) + 0.5f;
		cur_angle = player->dir.radians + atan2f(offset, proj_plane_dist);
		rays->walls[i] = cast_ray_to_wall(player->coords, cur_angle, map);
		rays->distances[i] = get_dist_to_wall(player->coords, rays->walls[i].coords);
		rays->distances[i] *= cosf(cur_angle - player->dir.radians);
		i++;
	}
}



void	init_textures(t_png_textures *pngs, t_textures *textures)
{
	pngs->north = mlx_load_png(textures->north);
}

int32_t	main(int argc, char **argv)
{
	static t_cub3d	info;

	if (argc != 2)
		return (EXIT_FAILURE);

	if (parse(argv[1], &info) == false)
		return (EXIT_FAILURE);

	mlx_set_setting(MLX_MAXIMIZED, true);
	info.mlx = mlx_init(DEFAULT_WIDTH, DEFAULT_HEIGHT, TITLE, true);
	if (info.mlx == NULL)
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}

	init_textures(&info.text, &info.textures);

	put_game_image(&info);
	put_minimap_image(&info);

	mlx_loop_hook(info.mlx, ft_hook, &info);
	mlx_resize_hook(info.mlx, on_resize, &info);
	mlx_loop(info.mlx);
	mlx_terminate(info.mlx);

	return (EXIT_SUCCESS);
}

static void	put_minimap_image(t_cub3d *info)
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

static void	put_game_image(t_cub3d *info)
{
	int32_t	width;
	int32_t	height;

	width = info->mlx->width;
	height = info->mlx->height;
	info->rays.count = width;
	info->rays.fov = 60.0f * M_PI / 180.0f;
	free(info->rays.walls);
	info->rays.walls = malloc(width * sizeof(t_wall_info));
	free(info->rays.distances);
	info->rays.distances = malloc(width * sizeof(float));
	get_all_rays(&info->rays, &info->map, &info->player);
	info->game = mlx_new_image(info->mlx, width, height);
	info->game_bs = get_block_size(&info->map, width, height);
	printf("New game_bs is %d\n", info->game_bs);
	printf("First ray distance %f\n", info->rays.distances[0]);
	printf("1/distance=%f\n", 1 / info->rays.distances[0]);
	printf("wall_width_in_px=width/distance=%d\n", (int)(width / info->rays.distances[0]));
	printf("one_pixel_on_texture=wall_width_in_px/text_size=%d\n", (int)(width / info->rays.distances[0]) / 8);
	put_game_screen(info->game, &info->textures, &info->text, &info->rays);
	mlx_image_to_window(info->mlx, info->game, 0, 0);
}

static void	on_resize(int32_t width, int32_t height, void *param)
{
	t_cub3d*	info;

	info = param;
	info->mlx->width = width;
	info->mlx->height = height;

	printf("Window resized: %d x %d\n", width, height);

	mlx_delete_image(info->mlx, info->game);
	put_game_image(info);

	mlx_delete_image(info->mlx, info->minimap);
	put_minimap_image(info);
}

static void	ft_hook(void *param)
{
	t_cub3d		*info;
	t_player	*player;

	info = param;
	player = &info->player;
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(info->mlx);
	else if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
		update_player_degree(player, player->dir.degree - PLAYER_ROT_STEP);
	else if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
		update_player_degree(player, player->dir.degree + PLAYER_ROT_STEP);
	else if (mlx_is_key_down(info->mlx, MLX_KEY_W))
		move_player(&info->map, &info->player, 90);
	else if (mlx_is_key_down(info->mlx, MLX_KEY_S))
		move_player(&info->map, &info->player, 270);
	else if (mlx_is_key_down(info->mlx, MLX_KEY_A))
		move_player(&info->map, &info->player, 0);
	else if (mlx_is_key_down(info->mlx, MLX_KEY_D))
		move_player(&info->map, &info->player, 190);
	get_all_rays(&info->rays, &info->map, &info->player);
	put_game_screen(info->game, &info->textures, &info->text, &info->rays);
	put_minimap(info);
}
