/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:03:39 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/11 17:27:48 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	flush(int fd);

bool	parse(char *filename, t_cub3d *info)
{
	int		fd;
	bool	result;

	fd = open(filename, O_RDONLY);
	result = false;
	if (fd)
	{
		if (parse_textures(fd, &info->textures))
		{
			if (parse_map(fd, &info->map, &info->player))
				result = true;
			else
			{
				free_textures(&info->textures);
				free_map(&info->map);
			}
		}
		else
		{
			flush(fd);
			free_textures(&info->textures);
		}
		close(fd);
	}
	return (result);
}

static void	flush(int fd)
{
	char	*line;

	while (set_gnl(fd, &line))
		free(line);
}
