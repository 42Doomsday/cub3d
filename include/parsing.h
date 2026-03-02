/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:58:19 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/02 18:08:21 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

#define TAB_SIZE 4
#define VALID_CHARS_MAP "\t\n\v\f\r 01NEWS"
#define VALID_PLAYER_SIDES "NEWS"
#define MAP_CHARACTERS "NEWS01"
#define EXTENSION ".cub"

#define FILL '2'
#define SPACE ' '

typedef struct s_coords
{
	int	x;
	int	y;
}	t_coords;

// map
char	**read_lines(int fd);
t_list	*expand_tabs(t_list *lst);
bool	flood_fill(char **map, int x, int y);
bool	is_contiguous(t_map *map);
void	trim_spaces(t_map *map);
void	trim_map(t_map *map);
void	free_map_data(char **data);
bool	validate_rgb(char *trim);

#endif
