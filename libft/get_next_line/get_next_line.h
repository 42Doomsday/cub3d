/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:17:13 by clouden           #+#    #+#             */
/*   Updated: 2026/02/04 19:20:17 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_buffer
{
	char	*buff;
	size_t	b;
	ssize_t	bytes;
	size_t	len;
}	t_buffer;

/* get_next_line.c */
char	*get_next_line(int fd);

/* get_next_line_utils.c */
int		ft_lengto(char *str);
char	*ft_grow_line(t_buffer *s, char *next);
int		ft_buffer_up(int fd, t_buffer *s);
char	*ft_nullout(t_buffer *s, char **next);
int		ft_phases(int fd, t_buffer *s, char **next);

#endif
