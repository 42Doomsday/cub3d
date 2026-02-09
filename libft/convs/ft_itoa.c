/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:04:53 by clouden           #+#    #+#             */
/*   Updated: 2025/05/21 20:21:25 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <libft.h>

static int	ft_getsize(long n, int neg)
{
	int	size;

	size = 2;
	if (neg == 1)
		size++;
	while (n >= 10)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

static char	*ft_ifzero(char *str)
{
	int	size;

	size = 2;
	str = ft_calloc(1, size);
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

static char	*ft_buildstr(long n, char *str, int size)
{
	str = ft_calloc(1, size);
	if (!str)
		return (NULL);
	size--;
	str[size] = '\0';
	while (n >= 0)
	{
		if (n == 0 && size == 0)
			return (str);
		else if (n == 0 && size == 1)
		{
			size--;
			str[size] = '-';
			return (str);
		}
		else
		{
			size--;
			str[size] = (n % 10) + '0';
			n /= 10;
		}
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;
	long	num;

	str = NULL;
	num = n;
	if (num == 0)
	{
		str = ft_ifzero(str);
		if (str == NULL)
			return (NULL);
		return (str);
	}
	if (num < 0)
	{
		num = num * -1;
		size = ft_getsize(num, 1);
	}
	else
		size = ft_getsize(num, 0);
	str = ft_buildstr(num, str, size);
	if (str == NULL)
		return (NULL);
	return (str);
}
/*
#include <stdio.h>

int main(void)
{
    int n0 = 0;
    int n1 = -2147483648;
    int n2 = -50;
    int n3 = -1101;

    printf("digit: %d\nstring: %s\n\n", n0, ft_itoa(n0));
    printf("digit: %d\nstring: %s\n\n", n1, ft_itoa(n1));
    printf("digit: %d\nstring: %s\n\n", n2, ft_itoa(n2));
    printf("digit: %d\nstring: %s\n\n", n3, ft_itoa(n3));
    return (0);
}
*/
