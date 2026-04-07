/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:32:40 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/07 16:42:31 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	init_mlx(t_cub3d *info);
static bool	init_textures(t_png_textures *pngs, t_textures *textures);
static bool	init_game(t_cub3d *info);
static void	destroy_textures(t_png_textures *pngs);

bool	init_info(t_cub3d *info, char *filename)
{
	ft_bzero(info, sizeof(t_cub3d));
	info->textures = &info->data.textures;
	info->map = &info->data.map;
	info->player = &info->data.player;
	info->layout = &info->data.layout;
	info->rays = &info->data.rays;
	info->pngs = &info->data.text;
	info->world = &info->data.world;
	info->world->map = info->map;
	info->world->player = info->player;
	if (is_valid_path(filename))
	{
		if (parse(filename, info->textures, info->map, info->player))
		{
			if (init_textures(info->pngs, info->textures))
			{
				if (init_mlx(info))
				{
					if (init_game(info))
						return (true);
					mlx_terminate(info->mlx);
				}
				destroy_textures(info->pngs);
			}
			free_map(info->map);
			free_textures(info->textures);
		}
	}
	return (false);
}

static bool	init_textures(t_png_textures *pngs, t_textures *textures)
{
	pngs->north = mlx_load_png(textures->north);
	if (pngs->north)
	{
		pngs->east = mlx_load_png(textures->east);
		if (pngs->east)
		{
			pngs->west = mlx_load_png(textures->west);
			if (pngs->west)
			{
				pngs->south = mlx_load_png(textures->south);
				if (pngs->south)
					return (true);
				mlx_delete_texture(pngs->west);
			}
			mlx_delete_texture(pngs->east);
		}
		mlx_delete_texture(pngs->north);
	}
	ft_putstr_fd("cub3d: can't open the texture\n", STDERR_FILENO);
	return (false);
}

static bool	init_mlx(t_cub3d *info)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	info->mlx = mlx_init(DEFAULT_WIDTH, DEFAULT_HEIGHT, TITLE, true);
	if (info->mlx == NULL)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
		return (false);
	}
	return (true);
}

static bool	init_game(t_cub3d *info)
{
	int	width;
	int	height;

	width = info->mlx->width;
	height = info->mlx->height;
	info->rays->count = width;
	info->rays->fov = 60.0f * M_PI / 180.0f;
	if (allocate_rays(info->rays, width))
	{
		calculate_angles(info->rays, info->player);
		info->game = mlx_new_image(info->mlx, width, height);
		if (info->game)
		{
			info->layout->game_bs = get_block_size(info->map, width, height);
			width *= 0.2f;
			height *= 0.2f;
			info->layout->minimap_bs = get_block_size(info->map, width, height);
			info->window = mlx_new_image(info->mlx, width, height);
			mlx_image_to_window(info->mlx, info->window, 0, 0);
			return (true);
		}
		free(info->rays->coords);
	}
	return (false);
}

static void	destroy_textures(t_png_textures *pngs)
{
	mlx_delete_texture(pngs->north);
	mlx_delete_texture(pngs->east);
	mlx_delete_texture(pngs->south);
	mlx_delete_texture(pngs->west);
}
