/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 17:39:36 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/06 17:39:51 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	put_square(mlx_image_t *minimap, t_render_obj square)
{
	int	i;
	int	j;

	j = 0;
	while (j < square.size)
	{
		i = 0;
		while (i < square.size)
		{
			mlx_put_pixel(minimap, square.x + i, square.y + j, square.colour);
			i++;
		}
		j++;
	}
}
