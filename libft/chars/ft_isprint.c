/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:07:46 by clouden           #+#    #+#             */
/*   Updated: 2025/05/21 15:52:23 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>
int main(void)
{
	int c;
	
	c = 13;

	printf("ft_isprint: %d\n", ft_isprint(c));
	printf("isprint: %d\n", isprint(c));
	printf("the character is: %c\n", (char)c);
	return (0);
}
*/
