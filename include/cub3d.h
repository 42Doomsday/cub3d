/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 11:54:27 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/07 14:51:04 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdarg.h>
# include <math.h>
# include <stdlib.h>

# include "libft.h"
# include "MLX42.h"
# include "state.h"
# include "core.h"

# define MAX_WIDTH             1024
# define DEFAULT_WIDTH         32
# define DEFAULT_HEIGHT        32
# define MINIMAP_PROCENT_SIZE  0.2f
# define TITLE                 "cub3d"

# define PLAYER_STEP      5
# define PLAYER_R         0.25f
# define PLAYER_HITBOX_R  0.3f
# define PLAYER_ROT_STEP  100
# define EPS              0.0001f
# define M_PI             3.14159265358979323846

// main
bool	init_info(t_cub3d *info, char *filename);
void	free_recourses(t_cub3d *info);
void	terminate_mlx(t_cub3d *info);

// parsing
bool	parse(char *filename, t_cub3d *info);
bool	is_valid_path(char *path);
void	free_map(t_map *map);
void	free_textures(t_textures *tex);

// rendering
void	put_minimap(t_cub3d *info);
void	put_game_screen(t_cub3d *info);

// utils
int		get_block_size(t_map *map, int32_t width, int32_t height);
int		get_rgba(int r, int g, int b, int a);
float	convert_degree_to_radians(float degree);
t_vec2	normilize(float radians);

#endif
