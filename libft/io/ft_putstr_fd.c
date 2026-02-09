/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:29:28 by clouden           #+#    #+#             */
/*   Updated: 2025/05/20 19:12:48 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	len = ft_strlen(s);
	write(fd, s, len);
}
/*
#include <stdio.h>

int main(void)
{
    char *s = "Hello is there anybody out there?";

    printf("original: %s", s);
    ft_putstr_fd(s, 1);
}
*/
