/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:01:11 by clouden           #+#    #+#             */
/*   Updated: 2025/05/23 19:17:59 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <libft.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	d_len;

	i = 0;
	d_len = ft_strlen(dst);
	if (size == 0 || (size == 1 && dst[0] == '\0'))
	{
		return (ft_strlen(src));
	}
	else if ((size == 1 && dst[0] != '\0') || \
			(size > 1 && d_len > size - 1))
	{
		return (size + ft_strlen(src));
	}
	else if (size > 1 && d_len == size - 1)
		return (d_len + ft_strlen(src));
	while (src[i] && d_len + i < size - 1)
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[d_len + i] = '\0';
	return (d_len + ft_strlen(src));
}
/* 
#include <stdio.h>
#include <bsd/string.h>

int main(void)
{
	//char *dst = NULL;
	char dst[30]; memset(dst, 0, 30);
	char *src = "AAAAAAAAA";
	size_t size = -1;

	//memset(dst, 'r', 15);
	size_t results = ft_strlcat(dst, src, size);
		
	printf("destination: %s\n", dst);
	printf("results: %zu\n", results);
	return (0);
}
*/
