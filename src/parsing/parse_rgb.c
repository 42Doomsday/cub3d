/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 22:34:30 by clouden           #+#    #+#             */
/*   Updated: 2026/03/04 14:15:31 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	validate_rgb(char *trim);
bool	comma_cnt(char *trim);
bool	check_num(char *str);
bool	check_length_arr(char **strarr);

int	*parse_rgb(char *val)
{
	char	**strarr;
	int		*intarr;
	int		i;

	strarr = ft_split(val, ',');
	intarr = ft_calloc(3, sizeof(int));
	if (!intarr)
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

bool	validate_rgb(char *val)
{
	int		i;
	int		cnt;
	char	**strarr;

	i = 0;
	cnt = 0;
	strarr = ft_split(val, ',');
	if (strarr)
	{
		if (comma_cnt(val) && check_length_arr(strarr))
		{
			while (strarr[i])
			{
				if (check_num(strarr[i]) == true)
					cnt++;
				i++;
			}
		}
		ft_strarr_free(&strarr);
	}
	return (cnt == 3);
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

bool	check_num(char *str)
{
	int	num;

	if (ft_isnum(str))
	{
		num = ft_atoi(str);
		if (num > -1 && num < 256)
			return (true);
	}
	return (false);
}

bool	check_length_arr(char **strarr)
{
	return (ft_strarr_len(strarr) == 3);
}
