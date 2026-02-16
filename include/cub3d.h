/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 11:54:27 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/16 15:35:39 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdarg.h>

# include "libft.h"

#define TAB_SIZE 4
#define VALID_CHARS_MAP "\t\n\v\f\r 01NEWS"
#define VALID_PLAYER_SIDES "NEWS"

typedef struct s_textures
{
	char *north;
	char *south;
	char *west;
	char *east;
	int	*floor;
	int	*ceiling;
}	t_textures;

typedef struct s_map
{
	char	**data;
	int		height;
	int		width;
}	t_map;

typedef struct s_player
{
	char	side;
	float	x;
	float	y;
}	t_player;

// parsers
bool	parse_textures(int fd, t_textures *out);
bool	parse_map(int fd, t_map *map, t_player *player);
bool	parse_player(char **map, t_player *player);

// validators
bool	is_valid_path(char *path);

// cleaning
void	free_map(t_map *map);

// helpers
char	**read_lines(int fd);

#endif
