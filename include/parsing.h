/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:58:19 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/23 14:02:04 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

typedef struct s_coords
{
	int	x;
	int	y;
}	t_coords;

char	**read_lines(int fd);
t_list	*expand_tabs(t_list *lst);
bool	flood_fill(char **map, int x, int y);
bool	is_contiguous(t_map *map);
void	trim_spaces(t_map *map);
void	trim_map(t_map *map);

#endif
