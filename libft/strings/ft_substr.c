/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:25:13 by clouden           #+#    #+#             */
/*   Updated: 2025/05/23 19:26:04 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <libft.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	l;

	if (!s)
		return (NULL);
	l = ft_strlen(s);
	if (start >= l)
		return (ft_calloc(1, sizeof(char)));
	if (len > l - start)
		len = l - start;
	sub = ft_calloc(1, len + 1);
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	return (sub);
}
/*
#include <stdio.h>

int main(void)
{
    char *s = "hola";
    unsigned int start = 0;
    size_t len = -1;

    printf("string: %s\nsubstr: %s\n", s, ft_substr(s, start, len));
    
    return (0);
}
*/
