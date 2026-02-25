/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 00:22:59 by clouden           #+#    #+#             */
/*   Updated: 2026/02/25 16:28:54 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(t_textures *tex);
void	print_error(char *error_type, char *message);

void	exit_with_error(t_textures *tex, char *error_type, char *message)
{
	print_error(error_type, message);
	free_textures(tex);
	exit(1);
}

void	print_error(char *error_type, char *message)
{
	ft_putstr_fd("Cub3D: ", 2);
	ft_putstr_fd(error_type, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

void	free_textures(t_textures *tex)
{
	if (!tex)
		return;
	free(tex->north);
	free(tex->south);
	free(tex->east);
	free(tex->west);
	free(tex->floor);
	free(tex->ceiling);
}

void	free_rgb(char ***strarr, int **intarr)
{
	if (strarr)
		ft_strarr_free(strarr);
	if (*intarr)
		free(*intarr);
	return ;
}

