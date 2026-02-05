/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:54:33 by clouden           #+#    #+#             */
/*   Updated: 2026/02/04 17:33:28 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_mapfmt(char *new, va_list args)
{
	unsigned long long	ptr;

	if (*new == 's')
		return (ft_putstr_fd(va_arg(args, const char *), 1));
	if (*new == 'd' || *new == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	if (*new == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1));
	if (*new == 'u')
		return (ft_putunbr_fd(va_arg(args, unsigned int), 1));
	if (*new == '%')
		return (ft_putchar_fd('%', 1));
	if (*new == 'x' || *new == 'X')
	{
		ptr = (unsigned long long)va_arg(args, unsigned int);
		return (ft_puthex_fd(ptr, 1, *new));
	}
	if (*new == 'p')
		return (ft_putptr_fd(va_arg(args, void *), 1));
	return (ft_putchar_fd(*new, 1));
}

int	ft_printf(const char *fmt, ...)
{
	va_list			args;
	char			*new;
	char			*old;
	ssize_t			bytes;	

	new = ft_strchr(fmt, '%');
	if (!new)
		return (write(1, fmt, ft_strlen(fmt)));
	va_start(args, fmt);
	bytes = write(1, fmt, new - fmt);
	while (new)
	{
		if (new[1] == '\0')
			return (va_end(args), bytes + write(1, new, 1));
		bytes += ft_mapfmt(++new, args);
		old = ++new;
		new = ft_strchr(new, '%');
		if (new)
			bytes += write(1, old, new - old);
		else
			bytes += write(1, old, ft_strlen(old));
	}
	return (va_end(args), bytes);
}
