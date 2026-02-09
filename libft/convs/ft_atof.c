/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:51:01 by clouden           #+#    #+#             */
/*   Updated: 2025/05/21 16:10:53 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	fraction(const char *str, struct s_float *f)
{
	str++;
	while (ft_isdigit(*str))
	{
		f->rnum = f->rnum * 10 + (*str - '0');
		f->zero = f->zero * 10;
		str++;
	}
	f->deci = (double)f->rnum / f->zero;
}

double	ft_atof(const char *str)
{
	struct s_float	f;

	f.sign = 1;
	f.lnum = 0;
	f.rnum = 0;
	f.deci = 0;
	f.zero = 1;
	if (*str == '\0')
		return (0);
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			f.sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		f.lnum = f.lnum * 10 + (*str - '0');
		str++;
	}
	if (*str == '.' || *str == ',')
		fraction(str, &f);
	return ((f.deci + f.lnum) * f.sign);
}
