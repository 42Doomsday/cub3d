/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:32:40 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/16 14:53:17 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	info_ptrs_setup(t_cub3d *info);
static bool	init_textures(t_png_textures *pngs, t_textures *textures);
static bool	init_rendering_layout(t_cub3d *info);

bool	init_info(t_cub3d *info, char *filename)
{
	ft_bzero(info, sizeof(t_cub3d));
	info_ptrs_setup(info);
	if (is_valid_path(filename))
	{
		if (parse(filename, info->textures, info->map, info->player))
		{
			if (init_textures(info->pngs, info->textures))
				if (init_rendering_layout(info))
					return (true);
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

bool	init_mlx(t_cub3d *info)
{
	mlx_t	*mlx;

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
	if (info->fullscreen)
		mlx = mlx_init(FULLSCREEN_WIDTH, FULLSCREEN_HEIGHT, TITLE, true);
	else
		mlx = mlx_init(MIN_WIDTH, MIN_HEIGHT, TITLE, true);
	if (mlx == NULL)
	{
		print_error("mlx", (char *)mlx_strerror(mlx_errno));
		return (false);
	}
	info->mlx = mlx;
	info->game = mlx_new_image(mlx, mlx->width, mlx->height);
	mlx_set_cursor_mode(mlx, MLX_MOUSE_HIDDEN);
	if (info->fullscreen)
		mlx_image_to_window(mlx, info->game, 0, 0);
	else
	{
		info->window = mlx_new_image(mlx, mlx->width, mlx->height);
		mlx_image_to_window(mlx, info->window, 0, 0);
	}
	return (true);
}

static bool	init_rendering_layout(t_cub3d *info)
{
	int	width;
	int	height;

	if (info->fullscreen)
	{
		width = FULLSCREEN_WIDTH;
		height = FULLSCREEN_HEIGHT;
	}
	else
	{
		width = MIN_WIDTH;
		height = MIN_HEIGHT;
	}
	info->rays->fov = 60.0f * M_PI / 180.0f;
	if (allocate_rays(info->rays, width))
	{
		calculate_angles(info->rays, info->player);
		info->layout->game_bs = get_block_size(info->map, width, height);
		width *= 0.2f;
		height *= 0.2f;
		info->layout->minimap_bs = get_block_size(info->map, width, height);
		return (true);
	}
	return (false);
}
