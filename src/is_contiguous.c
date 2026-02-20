/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_contiguous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:26:38 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/20 17:47:45 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char		**copy_map(char **map, int size);
static t_coords	get_first_map_character(char **map);
static bool		is_contain_not_filled(char **map);

bool	is_contiguous(t_map	*map)
{
	char		**map_copy;
	t_coords	start;
	bool		status;
	bool		result;

	result = false;
	map_copy = copy_map(map->data, map->height);
	if (map_copy)
	{
		start = get_first_map_character(map->data);
		status = flood_fill(map_copy, start.x, start.y);
		if (status && is_contain_not_filled(map_copy) == false)
			result = true;
		free_map_data(map_copy);
	}
	return (result);
}

static char	**copy_map(char **map, int size)
{
	char	**copy;
	int		i;
	int		j;

	copy = malloc((size + 1) * sizeof(char *));
	if (copy)
	{
		copy[size] = NULL;
		i = 0;
		while (i < size)
		{
			copy[i] = ft_strdup(map[i]);
			if (copy[i] == NULL)
			{
				j = 0;
				while (j < i)
					free(copy[j++]);
				free(copy);
				copy = NULL;
				break ;
			}
			i++;
		}
	}
	return (copy);
}

static t_coords	get_first_map_character(char **map)
{
	t_coords	coords;
	int		i;
	int		j;

	i = 0;
	coords.x = 0;
	coords.y = 0;
 	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr(MAP_CHARACTERS, map[i][j]) != NULL)
			{
				coords.x = j;
				coords.y = i;
				return (coords);
			}
			j++;
		}
		i++;
	}
	return (coords);
}

static bool	is_contain_not_filled(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != FILL && map[i][j] != SPACE)
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}
