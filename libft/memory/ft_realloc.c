/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 20:16:42 by clouden           #+#    #+#             */
/*   Updated: 2026/04/27 18:01:46 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_realloc(void *ptr, size_t size)
{
	size_t	i;
	void	*mem;

	i = 0;
	mem = malloc(size);
	while (i < size)
	{
		((unsigned char *)mem)[i] = 0;
		i++;
	}
	if (!ptr)
		return (mem);
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	i = 0;
	while (i < size || ((unsigned char *)ptr)[i])
	{
		((unsigned char *)mem)[i] = ((unsigned char *)ptr)[i];
		i++;
	}
	free(ptr);
	return (mem);
}
