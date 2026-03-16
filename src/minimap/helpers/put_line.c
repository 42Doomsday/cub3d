/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:56:48 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/16 18:19:18 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static t_icoords	get_step_xy(t_coords start, t_coords end);

void put_line(mlx_image_t *img, t_coords start, t_coords end, uint32_t color)
{
	t_icoords	xy;
	t_icoords	dxy;
	t_icoords	sxy;
	int		err;
	int		e2;

	dxy.x = abs((int)end.x - (int)start.x);
	dxy.y = abs((int)end.y - (int)start.y);
	sxy = get_step_xy(start, end);
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

static t_icoords	get_step_xy(t_coords start, t_coords end)
{
	t_icoords	step_xy;

	if (start.x < end.x)
		step_xy.x = 1;
	else
		step_xy.x = -1;
	if (start.y < end.y)
		step_xy.y = 1;
	else
		step_xy.y = -1;
	return (step_xy);
}
