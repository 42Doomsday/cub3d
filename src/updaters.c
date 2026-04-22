/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updaters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:15:12 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/22 15:33:12 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	exit_on_error(t_cub3d *info);

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
	if (info->states->fullscreen == false && width > MAX_WIDTH)
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
	if (mlx_resize_image(info->game, layout.game_width,
			layout.game_height) == false)
		exit_on_error(info);
	if (realloc)
	{
		free(info->rays->coords);
		if (allocate_rays(info->rays, info->layout->game_width) == NULL)
			exit_on_error(info);
	}
	if (info->states->fullscreen == false && info->layout->rescale)
	{
		if (mlx_resize_image(info->window, info->mlx->width,
				info->mlx->height) == false)
			exit_on_error(info);
	}
	calculate_angles(info->rays, info->player);
}

static void	exit_on_error(t_cub3d *info)
{
	print_error("cub3d", "can't update buffers");
	mlx_terminate(info->mlx);
	free_recourses(info);
	exit(2);
}
