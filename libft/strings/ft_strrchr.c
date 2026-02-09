/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:47:04 by clouden           #+#    #+#             */
/*   Updated: 2025/05/20 17:08:59 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	const char	*last_letter;

	c = (char)c;
	last_letter = (char *)0;
	if (c == 0)
	{
		while (*s)
			s++;
		last_letter = s;
		return ((char *)last_letter);
	}
	else
	{
		while (*s)
		{
			if (*s == c)
				last_letter = s;
			s++;
		}
		if (last_letter == 0)
			return ((char *)0);
		else
			return ((char *)last_letter);
	}
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
    char *s = "Hello World";
    int c = 'o';
    int n = '\0';
    int C = 'D';
    char *res;

    res = ft_strrchr(s, c);
    printf("ft_results: %s\n", res);
    
    res = strrchr(s, c);
    printf("results: %s\n", res);
    
    res = ft_strrchr(s, n);
    printf("ft_results: %s\n", res);
    
    res = strrchr(s, n);
    printf("results: %s\n", res);
     
    res = ft_strrchr(s, C);
    printf("ft_results: %s\n", res);
    
    res = strrchr(s, C);
    printf("results: %s\n", res);
    
}
*/
