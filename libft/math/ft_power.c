/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:58:28 by clouden           #+#    #+#             */
/*   Updated: 2025/10/15 15:53:25 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_power(int base, int exp)
{
	int	res;

	res = base * base;
	while (exp > 2)
	{
		res *= base;
		exp--;
	}
	return (res);
}

// #include <stdio.h>

// int main(void)
// {
// 	int base = 3;
// 	int exp = 2;
// 	int res;

// 	res = raise2power(base, exp);
// 	printf("raise %d to the %d power returns %d\n", base, exp, res);
// 	return (0);
// }
