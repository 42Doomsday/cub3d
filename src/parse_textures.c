/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:53:53 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/20 15:55:24 by clouden          ###   ########.fr       */
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

int	comma_cnt(char *trim)
{
	int	cnt;

	cnt = 0;
	while (*trim)
	{
		if (*trim == ',')
			cnt++;
		trim++;
	}
	return (cnt);
}

bool	check_range(int num)
{
	return (num > -1 && num < 256);
}

bool	validate_rgb(char **strarr)
{
	int	i;
	int	new;

	i = 0;
	if (!strarr || !*strarr || ft_strarr_len(strarr) != 3)
	{
		return (false);
	}
	while (strarr[i])
	{
		if (!ft_isnum(strarr[i]))
		{
			return (false);
		}
		new = ft_atoi(strarr[i]);
		if (!check_range(new))
			return (false);
		i++;
	}
	return (true);
}

void	free_rgb(char ***strarr, int **intarr)
{
	if (strarr)
		ft_strarr_free(strarr);
	if (*intarr)
		free(*intarr);
	return ;
}

int	*parse_rgb(char *trim)
{
	char	**strarr;
	int		*intarr;
	int		i;
	int		new;

	strarr = ft_split(trim, ',');
	intarr = ft_calloc(sizeof(int), 3);
	if (comma_cnt(trim) != 2 || !validate_rgb(strarr) || !intarr)
	{
		free_rgb(&strarr, &intarr);
		return (NULL);
	}
	if (validate_rgb(strarr))
	{
		i = 0;
		while (strarr[i])
		{
			intarr[i] = ft_atoi(strarr[i]);
			i++;
		}
		ft_strarr_free(&strarr);
		return (intarr);
	}
	else
	{
		free_rgb(&strarr, &intarr);
		return (NULL);
	}
}

