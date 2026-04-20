/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:32:40 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/17 21:01:41 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	info_ptrs_setup(t_cub3d *info);
static bool	init_mlx(t_cub3d *info);
static bool	init_textures(t_png_textures *pngs, t_textures *textures);
static bool	init_game(t_cub3d *info);

bool	init_mlx_2(t_cub3d *info)
{
	if (init_mlx(info))
	{
		if (init_game(info))
			return (true);
		mlx_terminate(info->mlx);
	}
	return (false);
}

bool	init_info(t_cub3d *info, char *filename)
{
	ft_bzero(info, sizeof(t_cub3d));
	info_ptrs_setup(info);
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

static void	info_ptrs_setup(t_cub3d *info)
{
	info->textures = &info->data.textures;
	info->map = &info->data.map;
	info->player = &info->data.player;
	info->layout = &info->data.layout;
	info->rays = &info->data.rays;
	info->pngs = &info->data.text;
	info->world = &info->data.world;
	info->world->map = info->map;
	info->world->player = info->player;
	info->sensitivity = 1.1f;
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
	print_error("config file", "can't open the texture");
	return (false);
}

static bool	init_mlx(t_cub3d *info)
{
	if (info->fullscreen)
	{
		mlx_set_setting(MLX_MAXIMIZED, false);
		mlx_set_setting(MLX_FULLSCREEN, true);
	}
	else
	{
		mlx_set_setting(MLX_FULLSCREEN, false);
		mlx_set_setting(MLX_MAXIMIZED, true);
	}
	info->mlx = mlx_init(DEFAULT_WIDTH, DEFAULT_HEIGHT, TITLE, true);
	if (info->mlx == NULL)
	{
		print_error("mlx", (char *)mlx_strerror(mlx_errno));
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
			if (info->fullscreen)
				mlx_image_to_window(info->mlx, info->game, 0, 0);
			else
			{
				info->window = mlx_new_image(info->mlx, width, height);
				mlx_image_to_window(info->mlx, info->window, 0, 0);
			}
			return (true);
		}
		free(info->rays->coords);
	}
	return (false);
}
