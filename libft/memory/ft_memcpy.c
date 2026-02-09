/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:04:28 by clouden           #+#    #+#             */
/*   Updated: 2025/10/15 14:09:43 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <libft.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if ((n == 0) || (dest == src))
		return (dest);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return ((void *)dest);
}
/*
#include <stdio.h>
#include <stddef.h>

int main(void)
{
	int src[] = {2000000000, 257,4}; 
	int ft_dest[] = {1,2,3};
	int dest[] = {1,2,3};
	size_t n = 5;	

	printf("ft_memcpy\n");
	printf("before [0] %d\n", ft_dest[0]);
	printf("before [1] %d\n", ft_dest[1]);
	printf("before [2] %d\n", ft_dest[2]);
	memcpy(ft_dest, src, n);
	printf("after [0] %d\n", ft_dest[0]);
	printf("after [1] %d\n", ft_dest[1]);
	printf("after [2] %d\n", ft_dest[2]);

	printf("memcpy\n");
	printf("before [0] %d\n", dest[0]);
	printf("before [1] %d\n", dest[1]);
	printf("before [2] %d\n", dest[2]);
	memcpy(dest, src, n);
	printf("after [0] %d\n", dest[0]);
	printf("after [1] %d\n", dest[1]);
	printf("after [2] %d\n", dest[2]);
	return (0);	
}
*/
