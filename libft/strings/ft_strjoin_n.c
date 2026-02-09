/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madird.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:56:50 by clouden           #+#    #+#             */
/*   Updated: 2025/08/27 12:57:29 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

// frees the first string 
// because the first arg of ft_stjoin_n is always a malloced process
// this is helper function only for ft_strjoin_n
static char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

char	*ft_strjoin_n(char **str_segs)
{
	int		i;
	char	*joined_str;

	if (!str_segs || !*str_segs)
		return (ft_calloc(1, 1));
	joined_str = ft_strdup(str_segs[0]);
	i = 1;
	while (str_segs[i])
	{
		joined_str = ft_strjoin_free(joined_str, str_segs[i]);
		i++;
	}
	return (joined_str);
}
