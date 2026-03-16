/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:28:23 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/16 18:23:55 by dkalgano         ###   ########.fr       */
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

void	put_player(t_cub3d *info);
void	put_line(mlx_image_t *img, t_coords start, t_coords end, uint32_t color);
void	put_circle(mlx_image_t *img, t_icoords center, int radius);

#endif
