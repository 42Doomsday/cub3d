/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 01:21:18 by clouden           #+#    #+#             */
/*   Updated: 2026/02/13 02:29:05 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	init_textures(t_textures *tex)
{
	tex->north = NULL;
	tex->south = NULL;
	tex->east = NULL;
	tex->west = NULL;
}
