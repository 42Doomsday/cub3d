/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:48:17 by clouden           #+#    #+#             */
/*   Updated: 2025/05/26 12:39:31 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = (char *)ft_calloc(len1 + len2 + 1, sizeof(char));
	if (new == NULL)
		return (NULL);
	while (i < len1)
	{
		new[i] = s1[i];
		i++;
	}
	while (i - len1 < len2)
	{
		new[i] = s2[i - len1];
		i++;
	}
	return (new);
}
/*
#include <stdio.h>

int main(void)
{
    char *s1 = "lorem ipsum";
    char *s2 = "dolor site amet";

    printf("%s", ft_strjoin(s1,s2));
    return (0);
}
*/
