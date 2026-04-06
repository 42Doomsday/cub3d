/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:03:39 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/06 17:10:36 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	flush(int fd);
static bool	protected_parsing(int fd, t_cub3d *info);

bool	parse(char *filename, t_cub3d *info)
{
	bool	result;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd > -1)
	{
		result = protected_parsing(fd, info);
		close(fd);
		return (result);
	}
	ft_putstr_fd("cub3d: can't open the configuration file\n", STDERR_FILENO);
	return (false);
}

static bool	protected_parsing(int fd, t_cub3d *info)
{
	if (parse_textures(fd, info->textures))
	{
		if (parse_map(fd, info->map, info->player))
			return (true);
		else
		{
			free_textures(info->textures);
			free_map(info->map);
		}
	}
	else
	{
		flush(fd);
		free_textures(info->textures);
	}
	return (false);
}

static void	flush(int fd)
{
	char	*line;

	while (set_gnl(fd, &line))
		free(line);
}
