/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:31:58 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/07 14:32:21 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COORDS_H
# define COORDS_H

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_coords
{
	float	x;
	float	y;
}	t_coords;

typedef struct s_icoords
{
	int	x;
	int	y;
}	t_icoords;

#endif
