/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 12:28:10 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/17 17:11:07 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_path(char *path)
{
	int		offset;
	size_t	path_len;
	size_t	extension_len;

	if (path)
	{
		path_len = ft_strlen(path);
		extension_len = ft_strlen(EXTENSION);
		if (path_len > extension_len)
		{
			offset = path_len - extension_len;
			if (ft_strncmp(&path[offset], EXTENSION, extension_len) == 0)
				return (true);
		}
	}
	return (false);
}
