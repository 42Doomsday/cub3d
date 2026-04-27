/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:21:36 by clouden           #+#    #+#             */
/*   Updated: 2026/04/27 18:03:46 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buffer	s;
	char			*next;
	int				n;
	int				status;

	next = NULL;
	n = 0;
	status = ft_phases(fd, &s, &next);
	if (status != 0)
		return (next);
	while (s.buff && s.buff[s.b] && s.buff[s.b] != '\n')
	{
		next[n] = s.buff[s.b];
		s.b++;
		if (s.buff[s.b] == '\0')
		{
			status = ft_phases(fd, &s, &next);
			if (status != 0)
				return (next);
		}
		n++;
	}
	if (s.buff[s.b] == '\n')
		next[n] = s.buff[s.b];
	return (++s.b, next);
}
