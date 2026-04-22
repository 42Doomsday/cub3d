/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 00:22:59 by clouden           #+#    #+#             */
/*   Updated: 2026/04/08 14:22:57 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_with_error(t_textures *tex, char *error_type, char *message)
{
	print_error(error_type, message);
	free_textures(tex);
	exit(1);
}

void	free_textures(t_textures *tex)
{
	if (!tex)
		return ;
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

bool	msg_on_error(bool result, char *error_type, char *message)
{
	if (result == false)
		print_error(error_type, message);
	return (result);
}
