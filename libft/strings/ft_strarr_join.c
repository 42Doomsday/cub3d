/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:18:18 by clouden           #+#    #+#             */
/*   Updated: 2025/08/01 19:18:41 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strarr_join(char **a1, char **a2)
{
	char	**jn;
	int		i;
	int		j;

	i = 0;
	j = 0;
	jn = ft_calloc((ft_strarr_len(a1) + ft_strarr_len(a2)) + 1, sizeof(char *));
	if (!jn)
		return (NULL);
	while (a1 && a1[i])
	{
		jn[i] = ft_strdup(a1[i]);
		if (!jn[i])
			return (ft_strarr_free(&jn), NULL);
		i++;
	}
	while (a2 && a2[j])
	{
		jn[i + j] = ft_strdup(a2[j]);
		if (!jn[i + j])
			return (ft_strarr_free(&jn), NULL);
		j++;
	}
	return (jn);
}
