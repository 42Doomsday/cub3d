/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 00:22:59 by clouden           #+#    #+#             */
/*   Updated: 2026/02/13 02:29:05 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	exit_with_error(t_textures *tex, char *error_type, char *detail)
{
	ft_putstr_fd("Cub3D: ", 2);
	ft_putstr_fd(error_type, 2);
	ft_putstr_fd(":", 2);
	ft_putstr_fd(detail, 2);
	free_textures(tex);
	exit(1);
}

void	free_textures(t_textures *tex)
{
	if (!tex)
		return;
	if (tex->north)
		free(tex->north);
	if (tex->south)
		free(tex->south);
	if (tex->east)
		free(tex->east);
	if (tex->west)
		free(tex->west);
}
