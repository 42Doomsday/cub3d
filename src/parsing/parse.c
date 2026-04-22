/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:03:39 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/08 14:13:41 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	flush(int fd);
static bool	process_parsing(int fd, t_textures *texts,
				t_map *map, t_player *player);

bool	parse(char *filename, t_textures *texts, t_map *map, t_player *player)
{
	bool	result;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd > -1)
	{
		result = process_parsing(fd, texts, map, player);
		close(fd);
		return (result);
	}
	print_error("config file", "can't open the configuration file");
	return (false);
}

static bool	process_parsing(int fd, t_textures *texts,
				t_map *map, t_player *player)
{
	if (parse_textures(fd, texts))
	{
		if (parse_map(fd, map, player))
			return (true);
		else
		{
			free_textures(texts);
			free_map(map);
		}
	}
	else
	{
		flush(fd);
		free_textures(texts);
	}
	return (false);
}

static void	flush(int fd)
{
	char	*line;

	while (set_gnl(fd, &line))
		free(line);
}
