/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:10:38 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/07 14:11:55 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_recourses(t_cub3d *info)
{
	free_map(info->map);
	free_textures(info->textures);
	mlx_delete_texture(info->text->north);
	mlx_delete_texture(info->text->south);
	mlx_delete_texture(info->text->east);
	mlx_delete_texture(info->text->west);
	free(info->rays->coords);
}

void	terminate_mlx(t_cub3d *info)
{
	mlx_delete_image(info->mlx, info->game);
	mlx_delete_image(info->mlx, info->window);
	mlx_terminate(info->mlx);
}
