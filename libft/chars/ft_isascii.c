/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:39:45 by clouden           #+#    #+#             */
/*   Updated: 2025/04/10 20:43:17 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

/*
#include <stdio.h>
#include <ctype.h>

int main(void)
{
	int c;
	
	c = 127;
	printf("ft_isascii: %d\n", ft_isascii(c));
	printf("isascii: %d\n", isascii(c));
	printf("The character is: %c", (char)c);
	return (0);
}
*/
