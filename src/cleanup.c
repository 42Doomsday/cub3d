/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:10:38 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/08 14:27:35 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_recourses(t_cub3d *info)
{
	free_map(info->map);
	free_textures(info->textures);
	mlx_delete_texture(info->pngs->north);
	mlx_delete_texture(info->pngs->south);
	mlx_delete_texture(info->pngs->east);
	mlx_delete_texture(info->pngs->west);
	free(info->rays->coords);
}

void	terminate_mlx(t_cub3d *info)
{
	mlx_delete_image(info->mlx, info->game);
	if (info->window)
		mlx_delete_image(info->mlx, info->window);
	mlx_terminate(info->mlx);
}

void	destroy_textures(t_png_textures *pngs)
{
	mlx_delete_texture(pngs->north);
	mlx_delete_texture(pngs->east);
	mlx_delete_texture(pngs->south);
	mlx_delete_texture(pngs->west);
}
