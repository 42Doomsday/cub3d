/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:44:25 by clouden           #+#    #+#             */
/*   Updated: 2025/05/20 17:17:04 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && *s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	else
		return ((unsigned char)s1[0] - (unsigned char)s2[0]);
}
/*
#include <string.h>
#include <stdio.h>

int main(void)
{
    char *s1 = "Hello World";
    char *s2 = "Hello";
    size_t n = 5;
    int res;

    res = ft_strncmp(s1, s2, n);
    printf("ft_results: %d\n", res);
    res = strncmp(s1, s2, n);
    printf("results: %d\n", res);
}
*/
