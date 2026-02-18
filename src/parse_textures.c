/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:53:53 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/18 14:04:06 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <libft.h>
//#include <fcntl.h>
//
//typedef struct s_textures
//{
//	char *north;
//	char *south;
//	char *east;
//	char *west;
//	int *floor;
//	int *ceiling;
//}	t_textures;
//
//bool	parse_textures(int fd, t_textures *out);
//
//int	main(void)
//{
//	int	fd;
//	t_textures	*out;
//
//	fd = open("../tests/examples/textures/invalid/incomplete_texture_path", O_RDONLY);
//	parse_textures(fd, out);
//	fd = open("../tests/examples/textures/invalid/partial_key_match", O_RDONLY);
//	parse_textures(fd, out);
//	fd = open("../tests/examples/textures/invalid/wrong_key", O_RDONLY);
//	parse_textures(fd, out);
//	return (0);
//}

#include "cub3d.h"

bool	check_for_tag(char *trim);
void	add_texture_vals(t_textures *out, char *str);
char	*extract_path(char *str);

bool	parse_textures(int fd, t_textures *out)
{
	char	*line = NULL;
	char	*trim = NULL;

	line = get_next_line(fd);
	dprintf(2, "LINE: %s\n", line);
	while (line)
	{
		if (line[0] == '\n')
		{
			free(line);
			line = NULL;
			line = get_next_line(fd);
			continue;
		}
		dprintf(2, "LINE: %s\n", line);
		trim = NULL;
		trim = ft_strtrim_wht(line);
		free(line);
		line = NULL;
		if (check_for_tag(trim))
		{
			add_texture_vals(out, trim);
		}
		else if (!check_for_tag(trim))
		{
			free(trim);
			trim = NULL;
			return (false);
		}
		free(trim);
		trim = NULL;
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	line = NULL;
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
		if (!ft_strncmp(trim, "NO", 2))
		{
			return (true);
		}
		else if (!ft_strncmp(trim, "SO", 2))
		{
			return (true);
		}
		else if (!ft_strncmp(trim, "EA", 2))
		{
			return (true);
		}
		else if (!ft_strncmp(trim, "WE", 2))
		{
			return (true);
		}
	}
	else if (ft_isspace(trim[1]))
	{
		if (!ft_strncmp(trim, "F", 1))
		{
			return (true);
		}
		if (!ft_strncmp(trim, "C", 1))
		{
			return (true);
		}
	}
	return (false);
}

void	add_texture_vals(t_textures *out, char *str)
{
	(void)out;
	extract_path(str);
}

char	*extract_path(char *str)
{
	int	offset;

	offset = 0;
	while (ft_isalpha(str[offset]))
		offset++;
	while (ft_isspace(str[offset]))
		offset++;
	dprintf(2, "EXTRACTED: %s\n", &str[offset]);
	return (&str[offset]);
}
