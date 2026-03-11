/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:56:48 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/11 17:30:29 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static t_ivec2	get_sxy(t_vec2 start, t_vec2 end);

void put_line(mlx_image_t *img, t_vec2 start, t_vec2 end, uint32_t color)
{
	t_ivec2	xy;
	t_ivec2	dxy;
	t_ivec2	sxy;
	int		err;
	int		e2;

	dxy.x = abs((int)end.x - (int)start.x);
	dxy.y = abs((int)end.y - (int)start.y);
	sxy = get_sxy(start, end);
	xy.x = start.x;
	xy.y = start.y;
	err = dxy.x - dxy.y;
	while (42)
	{
		mlx_put_pixel(img, xy.x, xy.y, color);
		if (xy.x == (int)end.x && xy.y == (int)end.y)
			break ;
		e2 = 2 * err;
		if (e2 > -dxy.y)
		{
			err -= dxy.y;
			xy.x += sxy.x;
		}
		if (e2 < dxy.x)
		{
			err += dxy.x;
			xy.y += sxy.y;
		}
	}
}

static t_ivec2	get_sxy(t_vec2 start, t_vec2 end)
{
	t_ivec2	sxy;

	if (start.x < end.x)
		sxy.x = 1;
	else
		sxy.x = -1;
	if (start.y < end.y)
		sxy.y = 1;
	else
		sxy.y = -1;
	return (sxy);
}
