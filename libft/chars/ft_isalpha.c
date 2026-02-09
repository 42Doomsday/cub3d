/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:57:30 by clouden           #+#    #+#             */
/*   Updated: 2025/05/20 13:12:04 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int main(void)
{
	int	c;

	c = '{';	
	printf("ft_isalpha: %d\nisalpha: %d\nthe character is: %c\n",\
		 ft_isalpha(c),ft_isalpha(c), (char)c);	
	return (0);
}
*/
