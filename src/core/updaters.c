/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updaters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:15:12 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/06 17:14:44 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_window_info(mlx_t *mlx, int width, int height)
{
	if (width < DEFAULT_WIDTH)
		width = DEFAULT_WIDTH;
	if (height <= DEFAULT_HEIGHT)
		height = DEFAULT_HEIGHT;
	mlx->width = width;
	mlx->height = height;
}

void	update_render_layour(t_cub3d *info, int width, int height)
{
	t_render_layout	*layout;
	t_map			*map;

	layout = info->layout;
	map = info->map;
	if (width > MAX_WIDTH)
	{
		layout->game_width = MAX_WIDTH;
		layout->game_height = MAX_WIDTH / ((float)width / (float)height);
		layout->game_bs = get_block_size(map, layout->game_width, layout->game_height);
		layout->rescale = true;
	}
	else
	{
		layout->game_width = width;
		layout->game_height = height;
		layout->game_bs = get_block_size(map, width, height);
		layout->rescale = false;
	}
	layout->minimap_width = layout->game_width * 0.2f;
	layout->minimap_height = layout->game_height * 0.2f;
	layout->minimap_bs = get_block_size(map, layout->minimap_width, layout->minimap_height);
}

void	update_buffers(t_cub3d *info, bool realloc)
{
	t_render_layout	layout;

	layout = *info->layout;
	info->rays->count = info->layout->game_width;
	mlx_resize_image(info->game, layout.game_width, layout.game_height);
	if (realloc)
	{
		free(info->rays->coords);
		allocate_rays(info->rays, info->layout->game_width);
	}
	if (info->layout->rescale)
		mlx_resize_image(info->window, info->mlx->width, info->mlx->height);
	calculate_angles(info->rays, info->player);
}
