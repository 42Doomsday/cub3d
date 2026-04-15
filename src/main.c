/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:54:04 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/15 14:51:01 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_frame(void *param);
static void	on_resize(int32_t width, int32_t height, void *param);
static void	ft_hook(void *param);
bool		init_mlx(t_cub3d *info);

int32_t	main(int argc, char **argv)
{
	t_cub3d	info;

	if (argc != 2)
	{
		print_error("filename", "missing");
		return (EXIT_FAILURE);
	}
	if (init_info(&info, argv[1]) == false)
	{
		print_error("init_info", "failed to start");
		return (EXIT_FAILURE);
	}
	while (info.exit_flag == false)
	{
		init_mlx(&info);
		/* update_window_info(info->mlx, width, height);
		update_render_layour(info, width, height);
		update_buffers(info, reallocate); */
		mlx_loop_hook(info.mlx, ft_hook, &info);
		mlx_resize_hook(info.mlx, on_resize, &info);
		mlx_loop_hook(info.mlx, get_frame, &info);
		mlx_loop(info.mlx);
		terminate_mlx(&info);
	}
	free_recourses(&info);
	return (EXIT_SUCCESS);
}

static void	on_resize(int32_t width, int32_t height, void *param)
{
	t_cub3d		*info;
	bool		reallocate;

	info = param;
	reallocate = width >= info->mlx->width;
	update_window_info(info->mlx, width, height);
	update_render_layour(info, width, height);
	update_buffers(info, reallocate);
}

static void	update_degree(t_cub3d *info, int change)
{
	int	new_degree;

	new_degree = info->player->dir.degree + (change * info->mlx->delta_time);
	update_player_degree(info->player, new_degree);
	calculate_angles(info->rays, info->player);
}

 void handle_mouse(t_cub3d *info)
 {
 	int x;
 	int y;
 	int center_x;
 	int center_y;
 	int dx;

 	center_x = info->mlx->width / 2;
 	center_y = info->mlx->height / 2;
 	mlx_get_mouse_pos(info->mlx, &x, &y);
	if (x > center_x)
		dx = x - center_x;
	else
		dx = x - center_x;
	printf("x : %d  x_cent : %d  dx : %d\n", x, center_x, dx);
 	update_degree(info, dx);
 	mlx_set_mouse_pos(info->mlx, center_x, center_y);
 }

static void	ft_hook(void *param)
{
	t_cub3d	*info;

	info = param;
	handle_mouse(info);
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(info->mlx);
		info->exit_flag = true;
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
		update_degree(info, -PLAYER_ROT_STEP);
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
		update_degree(info, PLAYER_ROT_STEP);
	if (mlx_is_key_down(info->mlx, MLX_KEY_W))
		move_player(info->world, 90, info->mlx->delta_time);
	if (mlx_is_key_down(info->mlx, MLX_KEY_S))
		move_player(info->world, 270, info->mlx->delta_time);
	if (mlx_is_key_down(info->mlx, MLX_KEY_A))
		move_player(info->world, 0, info->mlx->delta_time);
	if (mlx_is_key_down(info->mlx, MLX_KEY_D))
		move_player(info->world, 190, info->mlx->delta_time);
	if (mlx_is_key_down(info->mlx, MLX_KEY_F12))
	{
		info->fullscreen = (bool)!(info->fullscreen);
		mlx_close_window(info->mlx);
	}
}

static void	get_frame(void *param)
{
	t_cub3d	*info;

	info = param;
	//printf("fps: %f\n", 1 / (info->mlx->delta_time));
	get_all_rays(info->rays, info->map, info->player, info->game->height);
	put_game_screen(info->game, info->rays, info->textures, info->pngs);
	put_minimap(info->game, info->world, info->rays, info->layout->minimap_bs);
	if (info->fullscreen == false)
		mlx_scale_image_into(info->game, info->window);
}
