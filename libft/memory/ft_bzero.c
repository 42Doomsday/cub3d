/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:19:40 by clouden           #+#    #+#             */
/*   Updated: 2025/10/15 14:12:00 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	int ft_array[5] = {200000000, 456, 2};
	int array[5] = {200000000, 456, 2};
	int n = 2;

	printf("ft_bzero\n");
	printf("before array[0]: %d\n", ft_array[0]);
	printf("before array[1]: %d\n", ft_array[1]);
	printf("before array[2]: %d\n", ft_array[2]);
	printf("before array[3]: %d\n", ft_array[3]);
	ft_bzero(ft_array, n);	
	printf("after array[0]: %d\n", ft_array[0]);
	printf("after array[1]: %d\n", ft_array[1]);
	printf("after array[2]: %d\n", ft_array[2]);
	printf("after array[3]: %d\n", ft_array[3]);	


	printf("bzero\n");
	printf("before array[0]: %d\n", array[0]);
	printf("before array[1]: %d\n", array[1]);
	printf("before array[2]: %d\n", array[2]);
	printf("before array[3]: %d\n", array[3]);
	bzero(array, n);	
	printf("after array[0]: %d\n", array[0]);
	printf("after array[1]: %d\n", array[1]);
	printf("after array[2]: %d\n", array[2]);
	printf("after array[3]: %d\n", array[3]);
	return (0);	
}
*/
