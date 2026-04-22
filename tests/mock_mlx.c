/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/09 00:00:00 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mock_mlx.h"

/*
** Stub that replaces the real mlx_put_pixel. Writes RGBA bytes directly
** into the image's pixel buffer so tests can inspect the result.
*/
void	mlx_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	uint8_t	*p;

	if (!img || !img->pixels || x >= img->width || y >= img->height)
		return ;
	p = &img->pixels[(y * img->width + x) * 4];
	p[0] = (color >> 24) & 0xFF;
	p[1] = (color >> 16) & 0xFF;
	p[2] = (color >> 8) & 0xFF;
	p[3] = color & 0xFF;
}

mlx_image_t	*make_test_image(uint32_t w, uint32_t h)
{
	mlx_image_t	*img;

	img = calloc(1, sizeof(mlx_image_t));
	if (!img)
		return (NULL);
	*(uint32_t *)&img->width = w;
	*(uint32_t *)&img->height = h;
	img->pixels = calloc(w * h * 4, 1);
	if (!img->pixels)
	{
		free(img);
		return (NULL);
	}
	return (img);
}

void	free_test_image(mlx_image_t *img)
{
	if (!img)
		return ;
	free(img->pixels);
	free(img);
}

uint32_t	pixel_at(mlx_image_t *img, uint32_t x, uint32_t y)
{
	uint8_t	*p;

	p = &img->pixels[(y * img->width + x) * 4];
	return ((uint32_t)p[0] << 24 | (uint32_t)p[1] << 16
		| (uint32_t)p[2] << 8 | p[3]);
}
