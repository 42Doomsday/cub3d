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

#include "cub3d.h"

static t_player_draw	make_draw_params(t_cub3d *info);
static void				put_direction_ray(t_player_draw params, t_cub3d *info);


void	put_player(t_cub3d *info)
{
	t_player_draw	params;

	params = make_draw_params(info);
	put_direction_ray(params, info);
	put_circle(info->minimap, params.center, params.radius);
}


static t_player_draw	make_draw_params(t_cub3d *info)
{
	t_player_draw	params;
	t_player		*player;
	int				block_size;

	player = &info->player;
	block_size = info->minimap_bs;
	params.center.x = (int)(player->x * block_size);
	params.center.y = (int)(player->y * block_size);
	params.radius = block_size / 4;
	params.ray_len = block_size / 2;
	params.thickness = block_size / 20;
	params.dir_rad = (90.0f - info->player.dir) * M_PI / 180.0f;
	params.start_px.x = info->player.x * info->minimap_bs;
	params.start_px.y = info->player.y * info->minimap_bs;
	params.origin = get_player_vector(&info->player);
	return (params);
}


static void	put_direction_ray(t_player_draw prms, t_cub3d *info)
{
	float	fov;
	float	ray_angle;
	float	step;
	int		rays;
	int		i;

	fov = 60.0f * M_PI / 180.0f;
	rays = info->minimap->width / 10;
	step = fov / rays;
	i = 0;
	while (i < rays)
	{
		ray_angle = (prms.dir_rad - fov / 2) + step * i;
		prms.wall_coords = cast_ray_to_wall(prms.origin, ray_angle, &info->map);
		prms.end_px.x = prms.wall_coords.x * info->minimap_bs;
		prms.end_px.y = prms.wall_coords.y * info->minimap_bs;
		put_line(
			info->minimap,
			prms.start_px,
			prms.end_px,
			get_rgba(0, 215, 0, 200)
		);
		i++;
	}
}
