/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <dkalgano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by dkalgano         #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by dkalgano        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static t_player_draw	make_draw_params(t_cub3d *info);
static void				put_direction_ray(t_player_draw prms, t_cub3d *info, t_rays *rays);

void	put_player(t_cub3d *info)
{
	t_player_draw	params;

	params = make_draw_params(info);
	put_direction_ray(params, info, info->rays);
	put_circle(info->game, params.center, params.radius);
}

static t_player_draw	make_draw_params(t_cub3d *info)
{
	t_player_draw	params;
	int				block_size;

	block_size = info->layout->minimap_bs;
	params.center.x = (int)(info->player->coords.x * block_size);
	params.center.y = (int)(info->player->coords.y * block_size);
	params.radius = block_size / 4;
	params.start_px.x = info->player->coords.x * block_size;
	params.start_px.y = info->player->coords.y * block_size;
	return (params);
}

static void	put_direction_ray(t_player_draw prms, t_cub3d *info, t_rays *rays)
{
	size_t	i;

	i = 0;
	while (i < rays->count)
	{
		prms.end_px.x = rays->coords[i].x * info->layout->minimap_bs;
		prms.end_px.y = rays->coords[i].y * info->layout->minimap_bs;
		put_line(
			info->game,
			prms.start_px,
			prms.end_px,
			get_rgba(0, 215, 0, 255)
		);
		i++;
	}
}
