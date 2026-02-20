/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:31:28 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/20 17:34:49 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_map	*map)
{
	free_map_data(map->data);
}

void	free_map_data(char **data)
{
	int	idx;

	if (data == NULL)
		return ;
	idx = 0;
	while (data && data[idx])
		free(data[idx++]);
	free(data);
}
