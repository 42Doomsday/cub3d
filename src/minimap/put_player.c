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
	put_direction_ray(params, info, &info->rays);
	put_circle(info->minimap, params.center, params.radius);
}

static t_player_draw	make_draw_params(t_cub3d *info)
{
	t_player_draw	params;
	t_player		*player;
	int				block_size;

	player = &info->player;
	block_size = info->minimap_bs;
	params.center.x = (int)(player->coords.x * block_size);
	params.center.y = (int)(player->coords.y * block_size);
	params.radius = block_size / 4;
	params.ray_len = block_size / 2;
	params.thickness = block_size / 20;
	params.start_px.x = info->player.coords.x * info->minimap_bs;
	params.start_px.y = info->player.coords.y * info->minimap_bs;
	return (params);
}

static void	put_direction_ray(t_player_draw prms, t_cub3d *info, t_rays *rays)
{
	size_t	i;

	i = 0;
	while (i < rays->count)
	{
		prms.end_px.x = rays->coords[i].x * info->minimap_bs;
		prms.end_px.y = rays->coords[i].y * info->minimap_bs;
		put_line(
			info->minimap,
			prms.start_px,
			prms.end_px,
			get_rgba(0, 215, 0, 200)
		);
		i++;
	}
}
