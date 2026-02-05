/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:44:31 by clouden           #+#    #+#             */
/*   Updated: 2025/10/15 14:13:08 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		diff;

	i = 0;
	while (i < n)
	{
		diff = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
		if (diff != 0)
			return (diff);
		i++;
	}
	return (0);
}
/*
#include <string.h>
#include <stdio.h>

int main(void)
{
    char *s1 = "Hello, World!";
    char *s2 = "Hello, there!";
    size_t n = 16;
    
    printf("ft_result: %d\n", ft_memcmp(s1, s2, n));
    printf("result: %d\n", memcmp(s1, s2, n));

    int s3[] = {1,20,300,4000};
    int s4[] = {1,20,300,4444};
    
    printf("ft_result: %d\n",ft_memcmp(s3,s4,n));
    printf("result: %d\n",memcmp(s3,s4,n));

    char *s5 = "Hello, World!   ";
    char *s6 = "Hello, World!   ";
    
    printf("ft_result: %d\n", ft_memcmp(s5, s6, n));
    printf("result: %d\n", memcmp(s5, s6, n));


    return (0);  
}
*/
