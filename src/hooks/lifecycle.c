/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:56:56 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/20 15:03:02 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (info->minimap)
		put_minimap(info->game, info->world, info->rays,
			info->layout->minimap_bs);
	if (info->fullscreen == false && info->layout->rescale)
		mlx_scale_image_into(info->game, info->window);
}
