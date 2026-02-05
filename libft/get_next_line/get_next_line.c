/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:21:36 by clouden           #+#    #+#             */
/*   Updated: 2026/02/04 19:26:52 by clouden          ###   ########.fr       */
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

