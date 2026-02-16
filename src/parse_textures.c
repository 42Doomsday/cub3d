/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:53:53 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/16 11:55:49 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


bool	check_for_tag(char *trim);

bool	parse_textures(int fd, t_textures *out)
{
	char	*line;
	char	*trim;
	(void)out;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		printf("line: %s\n", line);
		trim = ft_strtrim_wht(line);
		free(line);
		printf("trim: %s\n", trim);
		line = get_next_line(fd);
		if (!check_for_tag(trim))
			return (false);
	}
	return (true);
}

bool	check_for_tag(char *trim)
{
	if (!ft_strncmp(trim, "NO", 2))
	{
		printf("NO in %s\n", trim);
		return (true);
	}
	if (!ft_strncmp(trim, "SO", 2))
	{
		printf("SO in %s\n", trim);
		return (true);
	}
	if (!ft_strncmp(trim, "EA", 2))
	{
		printf("EA in %s\n", trim);
		return (true);
	}
	if (!ft_strncmp(trim, "WE", 2))
	{
		printf("WE in %s\n", trim);
		return (true);
	}
	printf("TAG NOT FOUND\n");
	return (false);
}
