/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updaters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:15:12 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/20 13:45:00 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	compute_letterbox(int w, int h, t_render_layout *l, float asp);
static void	compute_game_size(t_render_layout *l, bool fullscreen);

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
	int32_t			mw;
	int32_t			mh;

	layout = info->layout;
	map = info->map;
	mlx_get_monitor_size(0, &mw, &mh);
	if (mh <= 0)
		mh = 9;
	if (mw <= 0)
		mw = 16;
	compute_letterbox(width, height, layout, (float)mw / (float)mh);
	compute_game_size(layout, info->fullscreen);
	layout->game_bs = get_block_size(map, layout->game_width,
			layout->game_height);
	layout->minimap_width = layout->game_width * MINIMAP_PROCENT_SIZE;
	layout->minimap_height = layout->game_height * MINIMAP_PROCENT_SIZE;
	layout->minimap_bs = get_block_size(map, layout->minimap_width,
			layout->minimap_height);
}

void	update_buffers(t_cub3d *info, bool realloc)
{
	t_render_layout	layout;

	layout = *info->layout;
	info->rays->count = layout.game_width;
	mlx_resize_image(info->game, layout.game_width, layout.game_height);
	if (realloc)
	{
		free(info->rays->coords);
		if (allocate_rays(info->rays, layout.game_width) == NULL)
			mlx_close_window(info->mlx);
	}
	if (info->fullscreen == false)
	{
		if (mlx_resize_image(info->window, layout.disp_width,
				layout.disp_height) == false)
			mlx_close_window(info->mlx);
		info->window->instances[0].x = layout.disp_x;
		info->window->instances[0].y = layout.disp_y;
	}
	calculate_angles(info->rays, info->player);
}

static void	compute_letterbox(int w, int h, t_render_layout *l, float asp)
{
	if ((float)w / (float)h > asp)
	{
		l->disp_height = h;
		l->disp_width = (int)((float)h * asp);
	}
	else
	{
		l->disp_width = w;
		l->disp_height = (int)((float)w / asp);
	}
	l->disp_x = (w - l->disp_width) / 2;
	l->disp_y = (h - l->disp_height) / 2;
}

static void	compute_game_size(t_render_layout *l, bool fullscreen)
{
	if (fullscreen == false && l->disp_width > MAX_WIDTH)
	{
		l->game_width = MAX_WIDTH;
		l->game_height = (int)((float)l->disp_height
				* (float)MAX_WIDTH / (float)l->disp_width);
	}
	else
	{
		l->game_width = l->disp_width;
		l->game_height = l->disp_height;
	}
}
