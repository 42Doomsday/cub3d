/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_mlx.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/09 00:00:00 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOCK_MLX_H
# define MOCK_MLX_H

# include "cub3d.h"

mlx_image_t	*make_test_image(uint32_t w, uint32_t h);
void		free_test_image(mlx_image_t *img);
uint32_t	pixel_at(mlx_image_t *img, uint32_t x, uint32_t y);

#endif
