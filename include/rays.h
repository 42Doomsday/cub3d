/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:00:51 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/22 15:47:22 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYS_H
# define RAYS_H

# include <stdlib.h>
# include "coords.h"
# include "texture.h"

typedef struct s_rays
{
	float			fov;
	size_t			count;
	t_coords		*coords;
	t_texture_id	*sides;
	float			*distances;
	int				*top_borders;
	int				*bot_borders;
	int				*heights;
	float			*angles;
	t_vec2			*norm_angles;
}	t_rays;

float			get_dist_to_wall(t_coords origin, t_coords wall);
t_coords		cast_ray_to_wall(t_coords origin, t_vec2 unit_vector,
					t_map *map);
t_coords		cast_ray_to_border(t_coords origin, t_vec2 unit_vector);
bool			is_wall(t_coords start, t_vec2 unit_vector, t_map *map);
bool			is_wall_or_space_on_coords(t_map *map, int x, int y);
t_texture_id	get_side_of_wall(t_coords wall, t_vec2 unit_vector);
void			get_all_rays(t_rays *rays, t_map *map, t_player *player,
					int height);
void			*allocate_rays(t_rays *rays, int width);
void			calculate_angles(t_rays *rays, t_player *player);

#endif
