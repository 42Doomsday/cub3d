/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:58:19 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/07 14:39:40 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

# define TAB_SIZE 4
# define VALID_CHARS_MAP "\t\n\v\f\r 01NEWS"
# define VALID_PLAYER_SIDES "NEWS"
# define MAP_CHARACTERS "NEWS01"
# define EXTENSION ".cub"

# define FILL '2'
# define SPACE ' '
# define WALL '0'

# define PARSER "parsing"
# define INV_CHARS "map contains unallowed characters"
# define INV_PLAYER "player positioning is invalid"
# define ISNT_CLOSED "map is not closed with walls"
# define ISNT_CONTIGUOUS "map isn't contiguous"

typedef enum e_error_class
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

// map
char	**read_lines(int fd);
t_list	*expand_tabs(t_list *lst);
bool	flood_fill(char **map, int x, int y);
bool	is_contiguous(t_map *map);
void	trim_spaces(t_map *map);
bool	trim_map(t_map *map);
void	free_map_data(char **data);
bool	validate_rgb(char *trim);
bool	is_closed(char **map, int height);

// general
bool	parse_textures(int fd, t_textures *out);
bool	parse_map(int fd, t_map *map, t_player *player);
bool	parse_player(char **map, t_player *player);
int		*parse_rgb(char *trim);

// common
bool	set_gnl(int fd, char **line);
void	exit_with_error(t_textures *tex, char *error_type, char *message);
void	print_error(char *error_type, char *message);
bool	msg_on_error(bool result, char *error_type, char *message);
void	free_map_data(char **data);
void	free_rgb(char ***strarr, int **intarr);

#endif
