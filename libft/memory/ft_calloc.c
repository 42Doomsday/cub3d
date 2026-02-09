/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:28:05 by clouden           #+#    #+#             */
/*   Updated: 2025/10/15 15:57:04 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	size_t	i;

	i = 0;
	if (count == 0 || size == 0)
		return (malloc(0));
	mem = malloc(count * size);
	if (!mem)
		return (NULL);
	while (i < (count * size))
	{
		((unsigned char *)mem)[i] = 0;
		i++;
	}
	return (mem);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
    size_t count = 3;
    size_t size = 4;
    void *ft_mem = ft_calloc(count, size);
    void *mem = calloc(count, size);

    printf("ft_calloc: %p, %zu\n", ft_mem, sizeof(ft_mem));
    printf("calloc: %p, %zu\n", mem, sizeof(mem));
    return (0);
}
*/
