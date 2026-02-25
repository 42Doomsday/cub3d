/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:53:53 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/25 21:28:46 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_for_tag(char *trim, t_textures *out);
void	add_texture_vals(t_textures *out, char *trim);
char	*extract_path(char *trim);
bool	verify_tex_struct(t_textures *tex);

static const t_texture_map  g_tex_map[] =
{ 
	{NORTH, "NO", offsetof(t_textures, north)},
	{SOUTH, "SO", offsetof(t_textures, south)},
	{EAST, "EA", offsetof(t_textures, east)},
	{WEST, "WE", offsetof(t_textures, west)},
	{T_COUNT, NULL, 0}
};

//	{FLOOR, "F", offsetof(t_textures, floor)},
//	{CEILING, "C", offsetof(t_textures, ceiling)},
//	{T_COUNT, NULL, NULL}
//};

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
		line = NULL;
		if (!check_for_tag(trim, out))
		{
			free(trim);
			return (false);
		}
		add_texture_vals(out, trim);
		free(trim);
		trim = NULL;
		line = get_next_line(fd);
	}
	if (!verify_tex_struct(out))
		return (false);
	return (true);
}

bool	check_for_tag(char *trim, t_textures *out)
{
	int		i;
	void	*mem_ptr;

	if ((ft_strlen(trim) > 3) && ft_isspace(trim[2]))
	{
		i = -1;
		while (g_tex_map[++i].name != NULL)
		{
			if (ft_strncmp(trim, g_tex_map[i].name, 2) == 0)
			{
				mem_ptr = (char *)out + g_tex_map[i].member;
				if(*(const char **)mem_ptr == NULL)
					return (true);
			}
		}
	}
	if ((ft_strlen(trim) > 2) && ft_isspace(trim[1]))
	{
		if (ft_strncmp(trim, "F", 1) == 0)
			return (true);
		if (ft_strncmp(trim, "C", 1) == 0)
			return (true);
	}
	print_error("invalid texture", trim);
	return (false);
}

void	add_texture_vals(t_textures *out, char *trim)
{
	char	*val;
	int		*rgb;
	void	*mem_ptr;
	int		i;
	
	val = ft_strdup(extract_path(trim));
	if (!val)
		return ;
	i = 0;
	while (g_tex_map[i].name != NULL)
	{
		if (ft_strncmp(trim, g_tex_map[i].name, 2) == 0)
		{
			mem_ptr = (char *)out + g_tex_map[i].member;
			*(const char **)mem_ptr = val;
		}
		i++;
	}
	rgb = parse_rgb(val);
	if (ft_strncmp(trim, "F", 1) == 0)
		out->floor = rgb;
	if (ft_strncmp(trim, "C", 1) == 0)
		out->ceiling = rgb;
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

bool	verify_tex_struct(t_textures *tex)
{
	if (!tex)
		return (false);
	return (tex->north &&
			tex->south &&
			tex->east &&
			tex->west &&
			tex->floor &&
			tex->ceiling);
}
