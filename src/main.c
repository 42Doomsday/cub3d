/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:54:04 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/20 18:30:19 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_hooks(mlx_t *mlx, t_cub3d *info);

int32_t	main(int argc, char **argv)
{
	t_cub3d	info;

	if (argc != 2)
	{
		print_error("filename", "missing");
		return (EXIT_FAILURE);
	}
	if (init_info(&info, argv[1]) == false)
	{
		print_error("init_info", "failed to start");
		return (EXIT_FAILURE);
	}
	while (info.exit_flag == false && init_mlx(&info))
	{
		update_render_layour(&info, info.mlx->width, info.mlx->height);
		update_buffers(&info, true);
		setup_hooks(info.mlx, &info);
		mlx_loop(info.mlx);
		if (info.pending_fullscreen)
		{
			info.fullscreen = !info.fullscreen;
			info.pending_fullscreen = false;
		}
		terminate_mlx(&info);
	}
	free_recourses(&info);
	return (EXIT_SUCCESS);
}

static void	setup_hooks(mlx_t *mlx, t_cub3d *info)
{
	mlx_loop_hook(mlx, movements_press_hook, info);
	mlx_key_hook(mlx, settings_press_hook, info);
	mlx_resize_hook(mlx, on_resize_hook, info);
	mlx_loop_hook(mlx, frame_hook, info);
	mlx_close_hook(mlx, close_hook, info);
	mlx_scroll_hook(mlx, scroll_hook, info);
}
