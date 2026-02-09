/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:22:57 by clouden           #+#    #+#             */
/*   Updated: 2025/05/20 19:09:27 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putchar_fd(char c, int fd)
{
	int	bytes;

	bytes = write(fd, &c, 1);
	return (bytes);
}
/*
#include <stdio.h>

int main(void)
{
	printf("size of char: %zu\n", sizeof(char));
	ft_putchar_fd('c',1);
}
*/
