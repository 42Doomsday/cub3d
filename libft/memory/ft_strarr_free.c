/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:05:04 by clouden           #+#    #+#             */
/*   Updated: 2025/10/15 15:59:22 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_strarr_free(char ***strarr)
{
	int	i;

	if (!strarr || !*strarr)
		return ;
	i = 0;
	while ((*strarr)[i])
	{
		free((*strarr)[i]);
		(*strarr)[i] = NULL;
		i++;
	}
	free(*strarr);
	*strarr = NULL;
}
