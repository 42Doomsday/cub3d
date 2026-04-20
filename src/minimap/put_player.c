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

static void	put_direction_ray(mlx_image_t *img, t_player_draw prms,
				t_rays *rays, int bs);

void	put_player(mlx_image_t *img, t_player *player, t_rays *rays, int bs)
{
	t_player_draw	params;

	params = make_draw_params(player, bs);
	put_direction_ray(img, params, rays, bs);
	put_circle(img, params.center, params.radius);
}

t_player_draw	make_draw_params(t_player *player, int bs)
{
	t_player_draw	params;

	params.center.x = (int)(player->coords.x * bs);
	params.center.y = (int)(player->coords.y * bs);
	params.radius = bs / 4;
	params.start_px.x = player->coords.x * bs;
	params.start_px.y = player->coords.y * bs;
	return (params);
}

static void	put_direction_ray(mlx_image_t *img, t_player_draw prms,
				t_rays *rays, int bs)
{
	size_t	i;

	i = 0;
	while (i < rays->count)
	{
		prms.end_px.x = roundf(rays->coords[i].x * bs);
		prms.end_px.y = roundf(rays->coords[i].y * bs);
		put_line(
			img,
			prms.start_px,
			prms.end_px,
			get_rgba(0, 215, 0, 255)
			);
		i++;
	}
}
