/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 12:28:10 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/17 17:04:02 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_path(char *path)
{
	int		offset;
	size_t	path_len;
	size_t	extention_len;

	if (path)
	{
		path_len = ft_strlen(path);
		extention_len = ft_strlen(EXTENTION);
		if (path_len > extention_len)
		{
			offset = path_len - extention_len;
			if (ft_strncmp(&path[offset], EXTENTION, extention_len) == 0)
				return (true);
		}
	}
	return (false);
}
