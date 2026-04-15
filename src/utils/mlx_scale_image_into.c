/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_scale_image_into.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 13:50:35 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/01 14:12:31 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_pixels(mlx_image_t *src, mlx_image_t *dst);

bool	mlx_scale_image_into(mlx_image_t *src, mlx_image_t *dst)
{
	uint32_t	b;

	if (!src || !dst || !src->pixels || !dst->pixels)
		return (false);
	if (!src->width || !src->height || !dst->width || !dst->height)
		return (false);
	if (src->width == dst->width && src->height == dst->height)
	{
		b = src->width * src->height * sizeof(int32_t);
		ft_memcpy(dst->pixels, src->pixels, b);
		return (true);
	}
	fill_pixels(src, dst);
	return (true);
}

static void	fill_pixels(mlx_image_t *src, mlx_image_t *dst)
{
	uint32_t	*s_px;
	uint32_t	*d_px;
	uint32_t	s_off;
	uint32_t	x;
	uint32_t	y;

	s_px = (uint32_t *)src->pixels;
	d_px = (uint32_t *)dst->pixels;
	y = 0;
	while (y < dst->height)
	{
		s_off = ((y * src->height) / dst->height) * src->width;
		x = 0;
		while (x < dst->width)
		{
			*d_px++ = s_px[s_off + ((x * src->width) / dst->width)];
			x++;
		}
		y++;
	}
}
