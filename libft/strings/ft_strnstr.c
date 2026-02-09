/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:38:00 by clouden           #+#    #+#             */
/*   Updated: 2025/05/23 19:14:39 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <libft.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nlen;
	size_t	hi;
	size_t	ni;

	nlen = ft_strlen(needle);
	hi = 0;
	ni = 0;
	if (nlen == 0)
		return ((char *)haystack);
	while (haystack[hi + ni] && (hi + ni) < len)
	{
		if (haystack[hi + ni] != needle[ni])
		{
			hi = hi + 1;
			ni = 0;
			continue ;
		}
		ni++;
		if (ni == nlen)
			return ((char *)haystack + hi);
	}
	return (NULL);
}
/*
#include <string.h>
#include <bsd/string.h>
#include <stdio.h>

int main(void)
{
    char haystack[30] = "aaabcabcd";
    char *needle = "aabc";
    size_t len = -1;

    printf("ft_results:	%s\n", ft_strnstr(haystack, needle, len));
    printf("results:	%s\n\n", strnstr(haystack, needle, len));
    
    char *needle1 = "a";

    printf("ft_results:	%s\n", ft_strnstr(haystack, needle1, len));
    printf("results:	%s\n\n", strnstr(haystack, needle1, len));

    char *needle2 = "b";

    printf("ft_results:	%s\n", ft_strnstr(haystack, needle2, len));
   	printf("results:	%s\n\n", strnstr(haystack, needle2, len)); 
} 
*/
