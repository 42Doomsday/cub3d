/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:08:20 by clouden           #+#    #+#             */
/*   Updated: 2025/05/20 13:19:06 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || \
		(c >= 'A' && c <= 'Z') || \
		(c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int main(void)
{
	int c;

	c = '@';
	printf("ft_isalnum: %d\n", ft_isalnum(c));
	printf("isalnum: %d\n", isalnum(c));
	printf("The character is: %c", (char)c);
	return (0);
}
*/
