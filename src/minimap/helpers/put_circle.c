/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_circle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:10:30 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/11 16:10:45 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_circle(mlx_image_t *img, t_ivec2 center, int radius)
{
	int	offset_x;
	int	offset_y;

	offset_y = -radius;
	while (offset_y <= radius)
	{
		offset_x = -radius;
		while (offset_x <= radius)
		{
			if (offset_x * offset_x + offset_y * offset_y <= radius * radius)
				mlx_put_pixel(img,
					center.x + offset_x,
					center.y + offset_y,
					get_rgba(0, 255, 0, 255));
			offset_x++;
		}
		offset_y++;
	}
}
