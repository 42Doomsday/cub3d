/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:53:53 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/18 18:36:47 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_for_tag(char *trim);
void	add_texture_vals(t_textures *out, char *str);
char	*extract_path(char *str);

bool	parse_textures(int fd, t_textures *out)
{
	char	*line;
	char	*trim;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		trim = ft_strtrim_wht(line);
		free(line);
		if (!check_for_tag(trim))
		{
			free(trim);
			return (false);
		}
		add_texture_vals(out, trim);
		free(trim);
		line = get_next_line(fd);
	}
	return (true);
}

bool	check_for_tag(char *trim)
{
	int	len;

	len = ft_strlen(trim);
	if (len < 3)
		return (false);
	if (ft_isspace(trim[2]))
	{
		if (ft_strncmp(trim, "NO", 2) == 0)
			return (true);
		if (ft_strncmp(trim, "SO", 2) == 0)
			return (true);
		if (ft_strncmp(trim, "EA", 2) == 0)
			return (true);
		if (ft_strncmp(trim, "WE", 2) == 0)
			return (true);
	}
	if (ft_isspace(trim[1]))
	{
		if (ft_strncmp(trim, "F", 1) == 0)
			return (true);
		if (ft_strncmp(trim, "C", 1) == 0)
			return (true);
	}
	return (false);
}

void	add_texture_vals(t_textures *out, char *str)
{
	char	*val;
	
	val = ft_strdup(extract_path(str));
	if (!val)
		return ;
	if (ft_strncmp(str, "NO", 2) == 0)
	{
		out->north = val;
		dprintf(2, "OUT: %s\n", out->north);
	}
	else if (ft_strncmp(str, "SO", 2) == 0)
	{
		out->south = val;
		dprintf(2, "OUT: %s\n", out->south);
	}
	else if (ft_strncmp(str, "EA", 2) == 0)
	{
		out->east = val;
		dprintf(2, "OUT: %s\n", out->east);
	}
	else if (ft_strncmp(str, "WE", 2) == 0)
	{
		out->west = val;
		dprintf(2, "OUT: %s\n", out->west);
	}
}

char	*extract_path(char *str)
{
	int	offset;

	offset = 0;
	while (ft_isalpha(str[offset]))
		offset++;
	while (ft_isspace(str[offset]))
		offset++;
	return (&str[offset]);
}

