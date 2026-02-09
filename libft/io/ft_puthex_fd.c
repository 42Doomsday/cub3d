/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:32:02 by clouden           #+#    #+#             */
/*   Updated: 2026/02/04 17:32:33 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_puthex_fd(unsigned long long n, int fd, char mode)
{
	int		bytes;
	char	*x;
	char	*upx;
	int		r;

	bytes = 0;
	x = "0123456789abcdef";
	upx = "0123456789ABCDEF";
	if (n >= 16)
		bytes += ft_puthex_fd(n / 16, fd, mode);
	r = n % 16;
	if (mode == 'x' || mode == 'p')
		bytes += ft_putchar_fd(x[r], fd);
	if (mode == 'X')
		bytes += ft_putchar_fd(upx[r], fd);
	return (bytes);
}

