/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:01:41 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/01 14:05:57 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	*get_malloc_arena(int width);

void	calculate_angles(t_rays *rays, t_player *player)
{
	float	proj_plane_dist;
	float	offset;
	size_t	i;

	proj_plane_dist = (rays->count / 2.0f) / tan(rays->fov / 2.0f);
	i = 0;
	while (i < rays->count)
	{
		offset = (rays->count - i) - (rays->count / 2.0f) + 0.5f;
		rays->angles[i] = player->dir.radians + atan2f(offset, proj_plane_dist);
		rays->norm_angles[i] = normilize(rays->angles[i]);
		i++;
	}
}

void	*allocate_rays(t_rays *rays, int width)
{
	void	*memory;

	memory = get_malloc_arena(width);
	if (memory)
	{
		rays->coords = memory;
		rays->sides = memory + width * sizeof(t_coords);
		rays->distances = (void *)rays->sides + width * sizeof(t_texture_id);
		rays->top_borders = (void *)rays->distances + width * sizeof(float);
		rays->bot_borders = (void *)rays->top_borders + width * sizeof(int);
		rays->heights = (void *)rays->bot_borders + width * sizeof(int);
		rays->angles = (void *)rays->heights + width * sizeof(int);
		rays->norm_angles = (void *)rays->angles + width * sizeof(float);
	}
	return (memory);
}

static void	*get_malloc_arena(int width)
{
	size_t	size;
	char	*allocation;

	size = sizeof(t_coords) + sizeof(t_texture_id) + sizeof(t_vec2);
	size += sizeof(float) * 2 + sizeof(int) * 3;
	allocation = malloc(width * size);
	return (allocation);
}
