/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:35:44 by clouden           #+#    #+#             */
/*   Updated: 2025/05/20 13:29:00 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i ++;
	return (i);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	char *s;

	s = "Hello";
	printf("strlen: %zu\n", ft_strlen(s));
	printf("strlen: %zu\n", strlen(s));
	printf("strlen: %s\n", s);
	return (0);
}
*/
