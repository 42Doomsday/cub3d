/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:56:53 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/20 15:03:21 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_mouse(t_cub3d *info);
static void	change_minimap_procent(t_render_layout *layout, t_map *map,
				float change);

void	movements_press_hook(void *param)
{
	t_cub3d	*info;

	info = param;
	handle_mouse(info);
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
}

void	settings_press_hook(mlx_key_data_t key, void *param)
{
	t_cub3d	*info;

	if (key.action == MLX_PRESS)
	{
		info = param;
		if (key.key == MLX_KEY_ESCAPE)
			close_hook(info);
		if (key.key == MLX_KEY_F12)
		{
			info->fullscreen = !info->fullscreen;
			mlx_close_window(info->mlx);
		}
		if (key.key == MLX_KEY_M)
			info->minimap = !info->minimap;
		if (key.key == MLX_KEY_MINUS)
			change_minimap_procent(info->layout, info->map, -0.1f);
		if (key.key == MLX_KEY_EQUAL)
			change_minimap_procent(info->layout, info->map, 0.1f);
	}
}

static void	change_minimap_procent(t_render_layout *layout, t_map *map,
	float change)
{
	float	new_procent;

	new_procent = layout->minimap_procent + change;
	if (new_procent >= MINIMAP_MIN_SIZE && new_procent <= MINIMAP_MAX_SIZE)
	{
		layout->minimap_procent = new_procent;
		update_minimap_layout(layout, map);
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
