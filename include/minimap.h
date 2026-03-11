/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:28:23 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/11 17:29:25 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3d.h"

typedef struct s_player_draw
{
	t_ivec2		center;
	t_vec2		start_px;
	t_vec2		end_px;
	t_vec2		wall_coords;
	int			radius;
	int			ray_len;
	int			thickness;
}	t_player_draw;

void	put_player(t_cub3d *info);
void	put_line(mlx_image_t *img, t_vec2 start, t_vec2 end, uint32_t color);
void	put_circle(mlx_image_t *img, t_ivec2 center, int radius);

#endif
