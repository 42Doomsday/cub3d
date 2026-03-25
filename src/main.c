/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:54:04 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/25 19:03:49 by dkalgano         ###   ########.fr       */
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

static void	*get_malloc_arena(int width);
static void	initialize(t_cub3d *info, bool reallocate);
static void	get_frame(t_cub3d *info);
static void	on_resize(int32_t width, int32_t height, void *param);
static void	ft_hook(void *param);

void	get_all_rays(t_rays *rays, t_map *map, t_player *player, int height)
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
		rays->coords[i] = cast_ray_to_wall(player->coords, cur_angle, map);
		rays->sides[i] = get_side_of_wall(rays->coords[i], normilize(cur_angle));
		rays->distances[i] = get_dist_to_wall(player->coords, rays->coords[i]);
		rays->distances[i] *= cosf(cur_angle - player->dir.radians);
		rays->heights[i] =  roundf(proj_plane_dist / rays->distances[i]);
		rays->top_borders[i] = (height / 2) - (rays->heights[i] / 2);
		rays->bot_borders[i] = (height / 2) + (rays->heights[i] / 2);
		i++;
	}
}

void	init_textures(t_png_textures *pngs, t_textures *textures)
{
	pngs->north = mlx_load_png(textures->north);
	pngs->east = mlx_load_png(textures->east);
	pngs->west = mlx_load_png(textures->west);
	pngs->south = mlx_load_png(textures->south);
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
	initialize(&info, true);

	mlx_loop_hook(info.mlx, ft_hook, &info);
	mlx_resize_hook(info.mlx, on_resize, &info);
	mlx_loop(info.mlx);
	mlx_terminate(info.mlx);

	return (EXIT_SUCCESS);
}

static void	on_resize(int32_t width, int32_t height, void *param)
{
	t_cub3d*	info;
	bool		reallocate;

	info = param;
	if (width < DEFAULT_WIDTH)
		width = DEFAULT_WIDTH;
	if (height <= DEFAULT_HEIGHT)
		height = DEFAULT_HEIGHT;
	reallocate = width >= info->mlx->width;
	info->mlx->width = width;
	info->mlx->height = height;

	printf("Window resized: %d x %d\n", width, height);
	initialize(info, reallocate);
	get_frame(info);
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
		move_player(&info->map, &info->player, 180);
	get_frame(info);
}

static void	*get_malloc_arena(int width)
{
	size_t	size;
	char	*allocation;

	size = sizeof(t_coords) + sizeof(t_texture_id) + sizeof(float) + sizeof(int) * 3;
	printf("memory ammount %lu\n", width * size);
	allocation = malloc(width * size);
	return (allocation);
}

static void	initialize(t_cub3d *info, bool reallocate)
{
	t_rays	*rays;
	void	*memory;
	int		width;
	int		height;
	int		margin;

	width = info->mlx->width;
	height = info->mlx->height;
	info->rays.count = width;
	info->rays.fov = 60.0f * M_PI / 180.0f;
	if (reallocate)
	{
		rays = &info->rays;
		free(rays->coords);
		memory = get_malloc_arena(info->mlx->width);
		rays->coords = memory;
		rays->sides = memory + info->mlx->width * sizeof(t_coords);
		rays->distances = (void *)rays->sides + width * sizeof(t_texture_id);
		rays->top_borders = (void *)rays->distances + width * sizeof(float);
		rays->bot_borders = (void *)rays->top_borders + width * sizeof(int);
		rays->heights = (void *)rays->bot_borders + width * sizeof(int);
	}

	if (info->game)
		mlx_delete_image(info->mlx, info->game);
	info->game = mlx_new_image(info->mlx, width, height);
	info->game_bs = get_block_size(&info->map, width, height);
	mlx_image_to_window(info->mlx, info->game, 0, 0);

	width *= 0.2f;
	height *= 0.2f;
	margin = width * 0.2f;
	if (info->minimap)
		mlx_delete_image(info->mlx, info->minimap);
	info->minimap = mlx_new_image(info->mlx, width, height);
	info->minimap_bs = get_block_size(&info->map, width, height);
	mlx_image_to_window(info->mlx, info->minimap, margin, margin);
}

static void	get_frame(t_cub3d *info)
{
	get_all_rays(&info->rays, &info->map, &info->player, info->game->height);
	put_game_screen(info);
	put_minimap(info);
}
