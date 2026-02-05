/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@studen42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:26:16 by clouden           #+#    #+#             */
/*   Updated: 2025/05/23 18:58:30 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>	

static int	ft_isnset(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		else
			i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	int		start;
	int		len;
	int		newidx;

	start = 0;
	len = ft_strlen(s1);
	while (ft_isnset(s1[start], set) && start < len)
		start++;
	while (ft_isnset(s1[len - 1], set) && start < len)
		len--;
	if (len - start <= 0)
		return (ft_strdup(""));
	new = (char *)ft_calloc(len - start + 1, sizeof(char));
	if (!new)
		return (NULL);
	newidx = 0;
	while ((start + newidx) < len)
	{
		new[newidx] = s1[start + newidx];
		newidx++;
	}
	return (new);
}

/*
#include <stdio.h>

int main(void)
{
	char *s1 = "xzxHelloxzxxz";
	char *set = "xz";
	char *s2 = "xzxxzxxz";
	char *s3 = "xzxxlzxxz";
	
	printf("orig: %s\nnew: %s\n\n", s1, ft_strtrim(s1, set));
	printf("orig: %s\nnew: %s\n\n", s2, ft_strtrim(s2, set));  
	printf("orig: %s\nnew: %s\n\n", s3, ft_strtrim(s3, set));  
	return (0);
}
*/
