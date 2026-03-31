/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_rescale_into.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 13:50:35 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/31 15:26:17 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		fill_pixels(mlx_image_t *src, mlx_image_t *dst);
static void		copy_row(mlx_image_t *src, mlx_image_t *dst, uint32_t j);
static uint32_t	get_pos(uint32_t d_pos, uint32_t d_sz, uint32_t s_sz);

bool	mlx_scale_image_into(mlx_image_t *src, mlx_image_t *dst)
{
	uint32_t	b;

	/* if (!src || !dst || !src->pixels || !dst->pixels)
		return (mlx_error(MLX_INVIMG));
	if (!src->width || !src->height || !dst->width || !dst->height)
		return (mlx_error(MLX_INVDIM)); */
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
	uint32_t	j;

	j = 0;
	while (j < dst->height)
	{
		copy_row(src, dst, j);
		j++;
	}
}

static void	copy_row(mlx_image_t *src, mlx_image_t *dst, uint32_t j)
{
	uint32_t	*s_px;
	uint32_t	*d_px;
	uint32_t	i;
	uint32_t	sy;
	uint32_t	sx;

	s_px = (uint32_t *)src->pixels;
	d_px = (uint32_t *)dst->pixels;
	sy = get_pos(j, dst->height, src->height) * src->width;
	i = 0;
	while (i < dst->width)
	{
		sx = get_pos(i, dst->width, src->width);
		d_px[j * dst->width + i] = s_px[sy + sx];
		i++;
	}
}

static uint32_t	get_pos(uint32_t d_pos, uint32_t d_sz, uint32_t s_sz)
{
	return ((uint32_t)((float)d_pos / (float)d_sz * (float)s_sz));
}

