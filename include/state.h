/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:45:38 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/07 14:46:49 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H

# include "MLX42.h"
# include "coords.h"
# include "texture.h"

typedef struct s_map
{
	char	**data;
	int		height;
	int		width;
}	t_map;

typedef struct s_direction
{
	float	degree;
	float	radians;
	t_vec2	unit;
}	t_direct;

typedef struct s_player
{
	t_direct	dir;
	t_coords	coords;
}	t_player;

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
	t_cub3d_data	data;
}	t_cub3d;

#endif
