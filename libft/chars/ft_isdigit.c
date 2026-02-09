/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:15:15 by clouden           #+#    #+#             */
/*   Updated: 2025/05/20 13:16:12 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
/*
#include <stdio.h>
#include <ctype.h>

int main(void)
{
	int c;

	c = ':';
	printf("ft_isdigit: %d\n", ft_isdigit(c));
	printf("isdigit: %d\n", isdigit(c));
	printf("the charcter is: %c", (char)c);
	return (0);
}
*/
