/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 11:05:56 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/23 12:29:27 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static bool	trim_empty_lines(t_map *map);
static bool	trim_spaces(t_map *map);
static int	count_extra_leading_spaces(char **map);
static int	count_extra_trailing_spaces(char **map);
static bool	is_empty_line(char *line);

static void	print_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
	printf("\n");
}

bool	trim_map(t_map *map)
{
	if (trim_empty_lines(map))
	{
		if (trim_spaces(map))
		{
			print_str_array(map->data);
			return (true);
		}
	}
	return (false);
}

static bool	trim_empty_lines(t_map *map)
{
	char	**data;
	int		idx;

	idx = 0;
	data = map->data;
	while (data && data[idx])
	{
		if (is_empty_line(data[idx]))
		{
			free(data[idx]);
			ft_memmove(data + idx, data + idx + 1, (map->height - idx) * sizeof(char *));
			map->height--;
			continue ;
		}
		idx++;
	}
	return (true);
}

static bool	trim_spaces(t_map *map)
{
	char	**data;
	int		count;
	int		i;

	data = map->data;
	count = count_extra_leading_spaces(map->data);
	i = 0;
	while (data && data[i])
	{
		ft_memmove(data[i], data[i] + count, ft_strlen(data[i]) - count + 1);
		i++;
	}
	count = count_extra_trailing_spaces(map->data);
	i = 0;
	while (data && data[i])
	{
		data[i][ft_strlen(data[i]) - count] = '\0';
		i++;
	}
	return (true);
}

static int	count_extra_leading_spaces(char **map)
{
	int	total;
	int	count;
	int	i;
	int	j;

	total = -1;
	i = 0;
	while (map && map[i])
	{
		count = 0;
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == SPACE)
				count++;
			else
				break ;
			j++;
		}
		if (total == -1 || count < total)
			total = count;
		i++;
	}
	return (total);
}

static int	count_extra_trailing_spaces(char **map)
{
	int	total;
	int	count;
	int	i;
	int	j;

	total = -1;
	i = 0;
	while (map && map[i])
	{
		count = 0;
		j = ft_strlen(map[i]);
		if (j > 0)
			j -= 1;
		while (j >= 0)
		{
			if (map[i][j] == SPACE)
				count++;
			else
				break ;
			j--;
		}
		if (total == -1 || count < total)
			total = count;
		i++;
	}
	return (total);
}

static bool	is_empty_line(char *line)
{
	int	idx;

	idx = 0;
	while (line && line[idx])
	{
		if (line[idx] != SPACE)
			return (false);
		idx++;
	}
	return (true);
}
