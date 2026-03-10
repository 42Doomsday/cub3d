/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 11:54:27 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/10 13:09:28 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdarg.h>
# include <math.h>

# include "libft.h"
# include "MLX42.h"

# define PARSERR "parsing"
# define INV_CHARS "map contains unallowed characters"
# define INV_PLAYER "player positioning is invalid"
# define ISNT_CLOSED "map is not closed with walls"
# define ISNT_CONTIGUOUS "map isn't contiguous"

# define PLAYER_STEP     0.142857f   /* 1.0f / 7.0f */
# define PLAYER_R        0.25f
# define PLAYER_HITBOX_R   0.3f
# define PLAYER_ROT_STEP 5.0f
# define EPS             0.0001f

# define M_PI 3.14159265358979323846
# define EPS 0.0001f

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;


typedef enum	e_texture
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	FLOOR,
	CEILING,
	T_COUNT
}	t_texture_id;

typedef struct s_textures
{
	char *north;
	char *south;
	char *west;
	char *east;
	int	*floor;
	int	*ceiling;
	int	*tex[T_COUNT];
}	t_textures;

typedef enum	e_error_class
{
	MAP,
	TEX,
	RGB,
}	t_error_class;

typedef struct s_error_class
{
	t_error_class	error_class;
	const char		message;
}	t_error_class_map;

typedef struct	s_texture_map
{
	t_texture_id	tex_id;
	const char		*name;
	size_t			member;
}   t_texture_map;

typedef struct s_map
{
	char	**data;
	int		height;
	int		width;
}	t_map;

typedef struct s_player
{
	float	rotation;
	float	x;
	float	y;
}	t_player;

typedef struct s_cub3d
{
	mlx_t		*mlx;
	t_textures	textures;
	t_map		map;
	t_player	player;
}	t_cub3d;

typedef struct s_ivec2
{
	int	x;
	int	y;
}	t_ivec2;

typedef struct s_player_draw
{
	mlx_image_t	*img;
	t_map		*map;
	t_ivec2		center;
	t_vec2		world_pos;
	int			block_size;
	int			radius;
	int			ray_len;
	int			thickness;
	float		angle;
}	t_player_draw;

// parsers
bool	parse_textures(int fd, t_textures *out);
bool	parse_map(int fd, t_map *map, t_player *player);
bool	parse_player(char **map, t_player *player);
int		*parse_rgb(char *trim);
bool	parse(char *filename, t_cub3d *info);

// validators
bool	is_valid_path(char *path);
// cleaning
void	free_map(t_map *map);
void	exit_with_error(t_textures *tex, char *error_type, char *message);
void	free_rgb(char ***strarr, int **intarr);
void	print_error(char *error_type, char *message);
bool	msg_on_error(bool result, char *error_type, char *message);
void	free_map_data(char **data);
void	free_textures(t_textures *tex);

// helpers
char	**read_lines(int fd);
t_list	*expand_tabs(t_list *lst);
bool	set_gnl(int fd, char **line);
bool	flood_fill(char **map, int x, int y);
bool	is_contiguous(t_map *map);
void	trim_spaces(t_map *map);
bool	trim_map(t_map *map);

// minimap
void	move_player_forward(t_map *map, t_player *player);
void	put_player(mlx_image_t *img, t_map *map, t_player *player);
int		get_rgba(int r, int g, int b, int a);
int		get_block_size(t_map *map, int32_t width, int32_t height);
t_vec2	cast_ray_to_border(t_vec2 origin, float angle);
t_vec2	cast_ray_to_wall(t_vec2 origin, float angle, t_map *map);
float	get_dist_to_wall(t_vec2 origin, float angle, t_map *map);
void	put_game_screen(mlx_image_t *img, t_map *map, t_player *player);

#endif
