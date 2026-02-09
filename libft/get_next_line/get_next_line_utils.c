/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 19:22:05 by clouden           #+#    #+#             */
/*   Updated: 2026/02/04 19:24:48 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "get_next_line.h"

char	*ft_nullout(t_buffer *s, char **next)
{
	if (s->buff)
	{
		free(s->buff);
		s->buff = NULL;
	}
	if (next && *next)
	{
		free(*next);
		*next = NULL;
	}
	return (NULL);
}

int	ft_lengto(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (*str != '\n' && *str != '\0')
	{
		len++;
		str++;
	}
	if (*str == '\n')
		return (++len);
	return (len);
}

char	*ft_grow_line(t_buffer *s, char *next)
{
	char	*newmem;
	int		n;

	n = 0;
	s->len = ft_lengto(next) + ft_lengto(&s->buff[s->b]);
	newmem = malloc(s->len + 1);
	if (newmem == NULL)
		return (NULL);
	ft_memset(newmem, 0, s->len + 1);
	if (next && next[0])
	{
		while (next[n])
		{
			newmem[n] = next[n];
			n++;
		}
		free(next);
		next = NULL;
	}
	return (newmem);
}

int	ft_buffer_up(int fd, t_buffer *s)
{
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	if (!s->buff)
	{
		s->buff = malloc(BUFFER_SIZE + 1);
		s->b = 0;
		if (!s->buff)
			return (0);
		s->buff = ft_memset(s->buff, 0, BUFFER_SIZE + 1);
	}
	if (s->buff && (s->buff[s->b] == 0 || s->b == 0))
	{
		s->b = 0;
		if (s->buff[0])
			s->buff = ft_memset(s->buff, 0, BUFFER_SIZE + 1);
		s->bytes = read(fd, s->buff, BUFFER_SIZE);
	}
	return (1);
}

int	ft_phases(int fd, t_buffer *s, char **next)
{
	if (!ft_buffer_up(fd, s) || s->bytes < 1)
	{
		if (s->bytes == 0)
		{
			free(s->buff);
			s->buff = NULL;
			return (1);
		}
		ft_nullout(s, next);
		return (-1);
	}
	*next = ft_grow_line(s, *next);
	if (!*next)
	{
		ft_nullout(s, next);
		return (-1);
	}
	return (0);
}
