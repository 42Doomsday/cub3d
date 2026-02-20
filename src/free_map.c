/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:31:28 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/13 14:38:10 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_map	*map)
{
	int	idx;

	if (map == NULL)
		return ;
	idx = 0;
	while (map->data && map->data[idx])
		free(map->data[idx++]);
	free(map->data);
}
