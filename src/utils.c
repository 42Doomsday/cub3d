/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:11:45 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/11 17:19:18 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_block_size(t_map *map, int32_t width, int32_t height)
{
	int	size1;
	int	size2;

	size1 = width / map->width;
	size2 = height / map->height;
	if (size1 < size2)
		return (size1);
	return (size2);
}
