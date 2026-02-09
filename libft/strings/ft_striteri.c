/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 00:07:13 by clouden           #+#    #+#             */
/*   Updated: 2025/05/20 19:05:42 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		f(i, &s[i]);
		i++;
	}
}
/*
static void mapper(unsigned int i, char *c)
{
    if (i == 0 || i % 5 == 0)
        *c = 'I';
    else if (i % 3 == 0)
        *c = 'r';
    else if (i % 2 != 0)
        *c = 't';
    else  if (i % 2 == 0)
        *c = 'e';
}

#include <stdio.h>

int main(void)
{
    char s[] = "Hello Strings";

    printf("Size of void *: %zu bytes\n", sizeof(void *));
    printf("Size of int  *: %zu bytes\n", sizeof(int *));
    printf("Size of char *: %zu bytes\n", sizeof(char *));

    printf("original: %s\n", s);
    ft_striteri(s, mapper);
    printf("inplace: %s\n", s);

    return (0);
}
*/
