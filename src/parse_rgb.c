/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 22:34:30 by clouden           #+#    #+#             */
/*   Updated: 2026/02/27 17:51:12 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	validate_rgb(char *trim, char **strarr);
bool	comma_cnt(char *trim);
bool	check_range(int num);
bool	check_length_arr(char **strarr);

int	*parse_rgb(char *val)
{
	char	**strarr;
	int		*intarr;
	int		i;

	strarr = ft_split(val, ',');
	intarr = ft_calloc(3, sizeof(int));
	if (!validate_rgb(val, strarr) || !intarr)
	{
		free_rgb(&strarr, &intarr);
		return (NULL);
	}
	i = 0;
	while (strarr[i])
	{
		intarr[i] = ft_atoi(strarr[i]);
		i++;
	}
	ft_strarr_free(&strarr);
	return (intarr);
}

bool	validate_rgb(char *val, char **strarr)
{
	int	i;
	int	new;

	i = 0;
	if (!strarr || !*strarr || !comma_cnt(val) || !check_length_arr(strarr))
		return (false);
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

bool	comma_cnt(char *trim)
{
	int	cnt;

	cnt = 0;
	while (*trim)
	{
		if (*trim == ',')
			cnt++;
		trim++;
	}
	return (cnt == 2);
}

bool	check_range(int num)
{
	return (num > -1 && num < 256);
}

bool	check_length_arr(char **strarr)
{
	return (ft_strarr_len(strarr) == 3);
}
