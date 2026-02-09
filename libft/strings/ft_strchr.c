/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:45:12 by clouden           #+#    #+#             */
/*   Updated: 2025/05/20 17:02:12 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return ((char *)0);
		else
			s++;
	}
	return ((char *)s);
}
/*
#include <string.h>
#include <stdio.h>

int main(void)
{
    char *s = "Hello";
    int c;
    int C;
    char *res;

    c = 'e';
    C = 'E';

    res = ft_strchr(s, c);
    printf("ft_returns: %s\n", res);
    res = strchr(s, c);
    printf("returns: %s\n", res);
    res = ft_strchr(s, C);
    printf("ft_returns: %s\n", res);
    res = strchr(s, C);
    printf("returns: %s\n", res);
    return (0);

}
*/
