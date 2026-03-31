/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:32:40 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/31 16:58:17 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	init_mlx(t_cub3d *info);
static bool	init_textures(t_png_textures *pngs, t_textures *textures);
static bool	init_game(t_cub3d *info);
static void	*allocate(t_rays *rays, int width);
static void	*get_malloc_arena(int width);

static void	destroy_textures(t_png_textures *pngs)
{
	mlx_delete_texture(pngs->north);
	mlx_delete_texture(pngs->east);
	mlx_delete_texture(pngs->south);
	mlx_delete_texture(pngs->west);
}

bool	init_info(t_cub3d *info, char *filename)
{
	ft_bzero(info, sizeof(t_cub3d));
	if (is_valid_path(filename) && parse(filename, info))
	{
		if (init_textures(&info->text, &info->textures))
		{
			if (init_mlx(info))
			{
				if (init_game(info))
					return (true);
				mlx_terminate(info->mlx);
			}
			destroy_textures(&info->text);
		}
		free_map(&info->map);
		free_textures(&info->textures);
	}
	return (false);
}

/* static void	fill_with_color(mlx_image_t *game)
{
	uint32_t	x;
	uint32_t	y;
	int			pixel;

	y = 0;
	pixel = get_rgba(255, 255, 255, 255);
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			mlx_put_pixel(game, x, y, pixel);
			x++;
		}
		y++;
	}
} */

void	update_info(t_cub3d *info, int org_width, int org_height, bool realloc)
{
	int	width;
	int	height;

	width = info->mlx->width;
	height = info->mlx->height;
	if (info->rescale)
	{
		info->rays.count = org_width;
		mlx_resize_image(info->game, org_width, org_height);
		if (realloc)
		{
			free(info->rays.coords);
			allocate(&info->rays, org_width);
		}
		info->game_bs = get_block_size(&info->map, org_width, org_height);
		if (info->game_rescaled)
			mlx_resize_image(info->game_rescaled, width, height);
		else
			info->game_rescaled = mlx_new_image(info->mlx, width, height);
		mlx_image_to_window(info->mlx, info->game_rescaled, 0, 0);
		width = org_width * 0.2f;
		height = org_width * 0.2f;
		mlx_resize_image(info->minimap, width, height);
		info->minimap_bs = get_block_size(&info->map, width, height);
		precalculate_angles(&info->rays, &info->player);
	}
	else
	{
		info->rays.count = width;
		mlx_resize_image(info->game, width, height);
		if (realloc)
		{
			free(info->rays.coords);
			allocate(&info->rays, width);
		}
		info->game_bs = get_block_size(&info->map, width, height);
		width *= 0.2f;
		height *= 0.2f;
		mlx_resize_image(info->minimap, width, height);
		info->minimap_bs = get_block_size(&info->map, width, height);
		precalculate_angles(&info->rays, &info->player);
	}
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

void	precalculate_angles(t_rays *rays, t_player *player)
{
	float	proj_plane_dist;
	float	offset;
	size_t	i;

	proj_plane_dist = (rays->count / 2.0f) / tan(rays->fov / 2.0f);
	i = 0;
	while (i < rays->count)
	{
		offset = (rays->count - i) - (rays->count / 2.0f) + 0.5f;
		rays->angles[i] = player->dir.radians + atan2f(offset, proj_plane_dist);
		rays->norm_angles[i] = normilize(rays->angles[i]);
		i++;
	}
}

static bool	init_game(t_cub3d *info)
{
	int	width;
	int	height;
	int	margin;

	width = info->mlx->width;
	height = info->mlx->height;
	info->rays.count = width;
	info->rays.fov = 60.0f * M_PI / 180.0f;
	if (allocate(&info->rays, width))
	{
		precalculate_angles(&info->rays, &info->player);
		info->game = mlx_new_image(info->mlx, width, height);
		if (info->game)
		{
			info->game_bs = get_block_size(&info->map, width, height);
			width *= 0.2f;
			height *= 0.2f;
			margin = width * 0.2f;
			info->minimap = mlx_new_image(info->mlx, width, height);
			info->minimap_bs = get_block_size(&info->map, width, height);
			return (true);
		}
		free(info->rays.coords);
	}
	return (false);
}

static void	*allocate(t_rays *rays, int width)
{
	void	*memory;

	memory = get_malloc_arena(width);
	if (memory)
	{
		rays->coords = memory;
		rays->sides = memory + width * sizeof(t_coords);
		rays->distances = (void *)rays->sides + width * sizeof(t_texture_id);
		rays->top_borders = (void *)rays->distances + width * sizeof(float);
		rays->bot_borders = (void *)rays->top_borders + width * sizeof(int);
		rays->heights = (void *)rays->bot_borders + width * sizeof(int);
		rays->angles = (void *)rays->heights + width * sizeof(int);
		rays->norm_angles = (void *)rays->angles + width * sizeof(float);
	}
	return (memory);
}

static void	*get_malloc_arena(int width)
{
	size_t	size;
	char	*allocation;

	size = sizeof(t_coords) + sizeof(t_texture_id) + sizeof(t_vec2);
	size += sizeof(float) * 2 + sizeof(int) * 3;
	allocation = malloc(width * size);
	return (allocation);
}
