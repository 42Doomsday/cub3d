/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:27:59 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/20 17:36:19 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const static int	g_dx[4] = {1, -1, 0, 0};
const static int	g_dy[4] = {0, 0, 1, -1};

static bool	add_back(t_list **queue, int i, int j);
t_coords	*pop(t_list **queue);
static bool	is_valid(char **map, int x, int y);
static bool	add_neighbors(t_list **queue, char **map, t_coords *coords);

bool	flood_fill(char **map, int x, int y)
{
	t_list		*queue;
	t_coords	*coords;
	bool		status;

	queue = NULL;
	if (add_back(&queue, x, y) == false)
		return (false);
	while (ft_lstsize(queue) > 0)
	{
		coords = pop(&queue);
		status = add_neighbors(&queue, map, coords);
		free(coords);
		if (status == false)
		{
			ft_lstclear(&queue, free);
			return (false);
		}
	}
	return (true);
}

static bool	add_back(t_list **queue, int x, int y)
{
	t_coords	*coords;
	t_list		*node;

	coords = malloc(sizeof(t_coords));
	if (coords)
	{
		coords->x = x;
		coords->y = y;
		node = ft_lstnew(coords);
		if (node)
		{
			ft_lstadd_back(queue, node);
			return (true);
		}
		free(coords);
	}
	return (false);
}

t_coords	*pop(t_list **queue)
{
	t_list		*node;
	t_coords	*coords;

	node = *queue;
	*queue = (*queue)->next;
	coords = node->content;
	free(node);
	return (coords);
}

static bool	add_neighbors(t_list **queue, char **map, t_coords *coords)
{
	int	idx;
	int	x;
	int	y;

	idx = 0;
	while (idx < 4)
	{
		x = coords->x + g_dx[idx];
		y = coords->y + g_dy[idx];
		if (is_valid(map, x, y))
		{
			map[y][x] = FILL;
			if (add_back(queue, x, y) == false)
				return (false);
		}
		idx++;
	}
	return (true);
}

/**
 * @brief Checks whether the character at the given coordinates
 *        is valid for flood fill.
 *
 * @param map 2D array of strings representing the map
 * @param x   X coordinate
 * @param y   Y coordinate
 *
 * @return true if:
 *         - coordinates are within bounds;
 *         - map[y] is not NULL;
 *         - x is within the string length;
 *         - character is not SPACE and not already FILL.
 *
 * @return false otherwise.
 */
static bool	is_valid(char **map, int x, int y)
{
	int	len;

	if (x < 0 || y < 0)
		return (false);
	if (map[y] == NULL)
		return (false);
	len = ft_strlen(map[y]);
	if (x >= len)
		return (false);
	if (map[y][x] == FILL || map[y][x] == SPACE)
		return (false);
	return (true);
}
