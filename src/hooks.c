/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:34:07 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/20 13:39:10 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_mouse(t_cub3d *info);

void	close_hook(void *param)
{
	t_cub3d	*info;

	info = param;
	mlx_close_window(info->mlx);
	info->exit_flag = true;
}

void	on_resize_hook(int32_t width, int32_t height, void *param)
{
	t_cub3d		*info;
	bool		reallocate;

	info = param;
	reallocate = width >= info->mlx->width;
	update_window_info(info->mlx, width, height);
	update_render_layour(info, width, height);
	update_buffers(info, reallocate);
}

void	frame_hook(void *param)
{
	t_cub3d	*info;

	info = param;
	get_all_rays(info->rays, info->map, info->player, info->game->height);
	put_game_screen(info->game, info->rays, info->textures, info->pngs);
	put_minimap(info->game, info->world, info->rays, info->layout->minimap_bs);
	if (info->fullscreen == false)
		mlx_scale_image_into(info->game, info->window);
}

void	control_hook(void *param)
{
	t_cub3d	*info;

	info = param;
	handle_mouse(info);
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		close_hook(info);
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
		info->fullscreen = !info->fullscreen;
		mlx_close_window(info->mlx);
	}
}

static void	handle_mouse(t_cub3d *info)
{
	int	x;
	int	y;
	int	center_x;
	int	center_y;
	int	dx;

	center_x = info->mlx->width / 2;
	center_y = info->mlx->height / 2;
	mlx_get_mouse_pos(info->mlx, &x, &y);
	if (x > center_x)
		dx = x - center_x;
	else
		dx = x - center_x;
	if (y > 0 && y < info->mlx->height && x > 0 && x < info->mlx->width)
	{
		update_degree(info, dx);
		mlx_set_mouse_pos(info->mlx, center_x, (center_y - y) / 4);
	}
}
