/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:34:01 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/07 14:36:29 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "stdlib.h"

typedef enum e_texture
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	FLOOR,
	CEILING,
	T_COUNT
}	t_texture_id;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		*floor;
	int		*ceiling;
	int		*tex[T_COUNT];
}	t_textures;

typedef struct s_texture_map
{
	t_texture_id	tex_id;
	const char		*name;
	size_t			member;
}	t_texture_map;

typedef struct s_png_textures
{
	mlx_texture_t	*north;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	mlx_texture_t	*south;
}	t_png_textures;

#endif
