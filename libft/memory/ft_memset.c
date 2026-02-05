/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:30:14 by clouden           #+#    #+#             */
/*   Updated: 2025/10/15 14:11:41 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned long long	pattern;
	int					blocks;
	int					remaining;
	int					i;

	blocks = n / 8;
	remaining = n % 8;
	pattern = (unsigned char)c;
	pattern |= pattern << 8;
	pattern |= pattern << 16;
	pattern |= pattern << 32;
	i = 0;
	while (i < blocks)
	{
		((unsigned long long *)s)[i] = pattern;
		i++;
	}
	i = 0;
	while (i < remaining)
	{
		((unsigned char *)s)[(blocks * 8) + i] = (unsigned char)c;
		i++;
	}
	return ((void *)s);
}
/*
#include <string.h>
#include <stdio.h>

int main(void)
{
	int ft_array[] = {2147483647, 260, 2, 40000, 3000000, 2, 70000, 800000};
	int array[] = {2147483647, 260, 2, 40000, 3000000, 2, 70000, 800000};
	int c = 0;
	int n = 21;
	
	printf("ft_memset\n");
	printf("antes array[0]: %d\n", ft_array[0]);
	printf("antes array[1]: %d\n", ft_array[1]);
	printf("antes array[2]: %d\n", ft_array[2]);
	printf("antes array[3]: %d\n", ft_array[3]);
	printf("antes array[4]: %d\n", ft_array[4]);
	printf("antes array[5]: %d\n", ft_array[5]);
	printf("antes array[6]: %d\n", ft_array[6]);
	printf("antes array[7]: %d\n", ft_array[7]);
	ft_memset(ft_array, c, n);
	printf("despues array[0]: %d\n", ft_array[0]);
	printf("despues array[1]: %d\n", ft_array[1]);
	printf("despues array[2]: %d\n", ft_array[2]);
	printf("despues array[3]: %d\n", ft_array[3]);
	printf("despues array[4]: %d\n", ft_array[4]);
	printf("despues array[5]: %d\n", ft_array[5]);
	printf("despues array[6]: %d\n", ft_array[6]);
	printf("despues array[7]: %d\n\n", ft_array[7]);

	printf("memset\n");
	printf("antes array[0]: %d\n", array[0]);
	printf("antes array[1]: %d\n", array[1]);
	printf("antes array[2]: %d\n", array[2]);
	printf("antes array[3]: %d\n", array[3]);
	printf("antes array[4]: %d\n", array[4]);
	printf("antes array[5]: %d\n", array[5]);
	printf("antes array[6]: %d\n", array[6]);
	printf("antes array[7]: %d\n", array[7]);
	memset(array, c, n);
	printf("despues array[0]: %d\n", array[0]);
	printf("despues array[1]: %d\n", array[1]);
	printf("despues array[2]: %d\n", array[2]);
	printf("despues array[3]: %d\n", array[3]);
	printf("despues array[4]: %d\n", array[4]);
	printf("despues array[5]: %d\n", array[5]);
	printf("despues array[6]: %d\n", array[6]);
	printf("despues array[7]: %d\n", array[7]);


	return (0);
}
*/
