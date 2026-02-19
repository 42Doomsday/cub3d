/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:53:53 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/19 18:29:47 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_for_tag(char *trim);
void	add_texture_vals(t_textures *out, char *trim);
char	*extract_path(char *trim);

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

void	add_texture_vals(t_textures *out, char *trim)
{
	char	*val;
	int *rgb;
	
	val = ft_strdup(extract_path(trim));
	if (!val)
		return ;
	if (ft_strncmp(trim, "NO", 2) == 0)
	{
		out->north = val;
		dprintf(2, "OUT: %s\n", out->north);
	}
	else if (ft_strncmp(trim, "SO", 2) =	= 0)
	{
		out->south = val;
		dprintf(2, "OUT: %s\n", out->south);
	}
	else if (ft_strncmp(trim, "EA", 2) == 0)
	{
		out->east = val;
		dprintf(2, "OUT: %s\n", out->east);
	}
	else if (ft_strncmp(trim, "WE", 2) == 0)
	{
		out->west = val;
		dprintf(2, "OUT: %s\n", out->west);
	}
	if (ft_strncmp(trim, "F", 1) == 0)
	{
		rgb = parse_rgb(trim);
		out->ceiling = rgb;
	}
	if (ft_strncmp(trim, "C", 1) == 0)
	{
		rgb = parse_rgb(trim);
		out->ceiling = rgb;
	}
}

char	*extract_path(char *trim)
{
	int	offset;

	offset = 0;
	while (ft_isalpha(trim[offset]))
		offset++;
	while (ft_isspace(trim[offset]))
		offset++;
	return (&trim[offset]);
}

// this counts commas
int	comma_cnt(char *trim)
{
	int	cnt;

	cnt = 0;
	while (*trim)
	{
		if (*trim == ",")
			cnt++;
		trim++;
	}
	return (cnt);
}

int	*parse_rgb(char *trim)
{
	char **strarr;

	if (comma_cnt(trim) != 2) // validate commas
		return (-1);
	strarr = ft_split(trim, ',');
	if (!strarr || !*strarr || ft_strarr_len(strarr) != 3) //validate length of arr
	{
		ft_strarr_free(&strarr);
		return (-1);
	}
	while (strarr)
	{
}
