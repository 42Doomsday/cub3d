/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:43:46 by clouden           #+#    #+#             */
/*   Updated: 2025/05/20 19:01:23 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <libft.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = ft_strlen(s);
	new = ft_calloc(1, len + 1);
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = f(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
/*
static char mapper(unsigned int i, char c)
{
    if (c == '\0')
        return (c);
    else if (i == 0 || i % 5 == 0)
        c = 'M';
    else if (i % 2 == 0)
        c = 'p';
    else if (i % 2 != 0)
        c = 'i';
    return (c);
}

#include <stdio.h>

int main(void)
{
    char *s = "Hello World";

    printf("original: %s\nmapped: %s\n", s, ft_strmapi(s, mapper));
    return (0);
}
*/
