/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updaters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:15:12 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/20 14:43:08 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_window_info(mlx_t *mlx, int width, int height)
{
	if (width < MIN_WIDTH)
		width = MIN_WIDTH;
	if (height <= MIN_HEIGHT)
		height = MIN_HEIGHT;
	mlx->width = width;
	mlx->height = height;
}

void	update_render_layour(t_cub3d *info, int width, int height)
{
	t_render_layout	*layout;
	t_map			*map;

	layout = info->layout;
	map = info->map;
	if (info->fullscreen == false && width > MAX_WIDTH)
	{
		layout->game_width = MAX_WIDTH;
		layout->game_height = MAX_WIDTH / ((float)width / (float)height);
		layout->game_bs = get_block_size(map, layout->game_width,
				layout->game_height);
		layout->rescale = true;
	}
	else
	{
		layout->game_width = width;
		layout->game_height = height;
		layout->game_bs = get_block_size(map, width, height);
		layout->rescale = false;
	}
	update_minimap_layout(layout, map);
}

void	update_minimap_layout(t_render_layout *layout, t_map *map)
{
	layout->minimap_width = layout->game_width * layout->minimap_procent;
	layout->minimap_height = layout->game_height * layout->minimap_procent;
	layout->minimap_bs = get_block_size(map, layout->minimap_width,
			layout->minimap_height);
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
		if (allocate_rays(info->rays, info->layout->game_width) == NULL)
			mlx_close_window(info->mlx);
	}
	if (info->fullscreen == false && info->layout->rescale)
		if (mlx_resize_image(info->window, info->mlx->width,
				info->mlx->height) == false)
			mlx_close_window(info->mlx);
	calculate_angles(info->rays, info->player);
}
