/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:28:23 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/07 16:06:55 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3d.h"

typedef struct s_player_draw
{
	t_icoords	center;
	t_coords	start_px;
	t_coords	end_px;
	int			radius;
}	t_player_draw;

typedef struct s_render_obj
{
	int		x;
	int		y;
	int		size;
	int32_t	colour;
}	t_render_obj;

void			put_player(mlx_image_t *img, t_player *player,
					t_rays *rays, int bs);
t_player_draw	make_draw_params(t_player *player, int bs);
void	put_line(mlx_image_t *img, t_coords start, t_coords end,
			uint32_t color);
void	put_circle(mlx_image_t *img, t_icoords center, int radius);
void	put_square(mlx_image_t *minimap, t_render_obj square);

#endif
