/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:54:04 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/20 13:39:56 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		mlx_loop_hook(info.mlx, control_hook, &info);
		mlx_resize_hook(info.mlx, on_resize_hook, &info);
		mlx_loop_hook(info.mlx, frame_hook, &info);
		mlx_close_hook(info.mlx, close_hook, &info);
		mlx_loop(info.mlx);
		terminate_mlx(&info);
	}
	free_recourses(&info);
	return (EXIT_SUCCESS);
}




