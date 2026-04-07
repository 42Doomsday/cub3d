/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:28:39 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/07 14:52:44 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "state.h"

// rays
float			get_dist_to_wall(t_coords origin, t_coords wall);
t_coords		cast_ray_to_wall(t_coords origin, t_vec2 unit_vector,
					t_map *map);
bool			is_wall(t_coords start, t_vec2 unit_vector, t_map *map);
bool			is_wall_or_space_on_coords(t_map *map, int x, int y);
t_texture_id	get_side_of_wall(t_coords wall, t_vec2 unit_vector);
void			get_all_rays(t_rays *rays, t_map *map, t_player *player,
					int height);
void			*allocate_rays(t_rays *rays, int width);
void			calculate_angles(t_rays *rays, t_player *player);

// player
void			move_player(t_cub3d *info, float degree);
void			update_player_degree(t_player *player, float degree);

// updates
void			update_window_info(mlx_t *mlx, int width, int height);
void			update_render_layour(t_cub3d *info, int width, int height);
void			update_buffers(t_cub3d *info, bool realloc);

// scaler
bool			mlx_scale_image_into(mlx_image_t *src, mlx_image_t *dst);

#endif
