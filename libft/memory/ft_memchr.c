/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:49:17 by clouden           #+#    #+#             */
/*   Updated: 2025/10/15 14:12:50 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)((unsigned char *)s + i));
		i++;
	}
	return ((void *)0);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
    int s[] = {1, 2000, 30};
    int num = 30;
    size_t n = 10;
    char s1[] = "apples suck";
    int c = 'p';
    int C = 'P';

    printf("char: %d, ft_returns: %p\n", num, ft_memchr(s, num, n));
    printf("char: %d, norm_retns: %p\n\n", num, memchr(s, num, n));

    printf("char: %c, ft_returns: %p\n", C, ft_memchr(s1, C, n));
    printf("char: %c, norm_retns: %p\n\n", C, memchr(s1, C, n));

    printf("char: %c, ft_returns: %p\n", c, ft_memchr(s1, c, n));
    printf("char: %c, norm_retns: %p\n", c, memchr(s1, c, n));
}
*/
