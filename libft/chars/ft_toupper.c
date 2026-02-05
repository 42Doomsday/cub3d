/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:56:05 by clouden           #+#    #+#             */
/*   Updated: 2025/05/20 16:52:50 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}
/*
#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char a = 'a';
    char Z = 'Z';
    char m = 'm';
    int n = 26;

    printf("%c toupper: %c ft_toupper: %c\n", a, toupper(a), ft_toupper(a)); 
    printf("%c toupper: %c ft_toupper: %c\n", Z, toupper(Z), ft_toupper(Z)); 
    printf("%c toupper: %c ft_toupper: %c\n", m, toupper(m), ft_toupper(m)); 
    printf("%d toupper: %d ft_toupper: %d\n", n, toupper(n), ft_toupper(n));
    return (0);
}
*/
