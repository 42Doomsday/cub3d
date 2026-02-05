/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:13:55 by clouden           #+#    #+#             */
/*   Updated: 2025/05/20 16:55:55 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}
/*
#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char A = 'A';
    char z = 'z';
    char M = 'M';
    int n = 26;

    printf("%c tolower: %c ft_tolower: %c\n", A, tolower(A), ft_tolower(A));
    printf("%c tolower: %c ft_tolower: %c\n", z, tolower(z), ft_tolower(z));
    printf("%c tolower: %c ft_tolower: %c\n", M, tolower(M), ft_tolower(M));
    printf("%d tolower: %d ft_tolower: %d\n", n, tolower(n), ft_tolower(n));
    return (0);
}
*/
