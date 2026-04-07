/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 11:54:27 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/07 16:35:36 by dkalgano         ###   ########.fr       */
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
# include "world.h"
# include "rays.h"

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

typedef struct s_render_layout
{
	int		game_bs;
	int		game_width;
	int		game_height;
	int		minimap_bs;
	int		minimap_width;
	int		minimap_height;
	bool	rescale;
}	t_render_layout;

typedef struct s_cub3d_data
{
	t_textures		textures;
	t_map			map;
	t_player		player;
	t_render_layout	layout;
	t_rays			rays;
	t_png_textures	text;
	t_world			world;
}	t_cub3d_data;

typedef struct s_cub3d
{
	mlx_t			*mlx;
	t_textures		*textures;
	t_map			*map;
	t_player		*player;
	mlx_image_t		*game;
	mlx_image_t		*window;
	t_render_layout	*layout;
	t_rays			*rays;
	t_png_textures	*text;
	t_world			*world;
	t_cub3d_data	data;
}	t_cub3d;

// main
bool	init_info(t_cub3d *info, char *filename);
void	free_recourses(t_cub3d *info);
void	terminate_mlx(t_cub3d *info);

// parsing
bool	parse(char *filename, t_cub3d *info);
bool	is_valid_path(char *path);

// rendering
void	put_minimap(mlx_image_t *img, t_world *world, t_rays *rays, int bs);
void	put_game_screen(mlx_image_t *img, t_rays *rays, t_textures *texts,
			t_png_textures *pngs);

// utils
int		get_block_size(t_map *map, int32_t width, int32_t height);
int		get_rgba(int r, int g, int b, int a);
float	convert_degree_to_radians(float degree);
t_vec2	normilize(float radians);

// updaters
void	update_window_info(mlx_t *mlx, int width, int height);
void	update_render_layour(t_cub3d *info, int width, int height);
void	update_buffers(t_cub3d *info, bool realloc);
bool	mlx_scale_image_into(mlx_image_t *src, mlx_image_t *dst);

#endif
