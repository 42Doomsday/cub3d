/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_closed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:27:53 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/02 17:34:23 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	puterror(char *filename);
static void unexpected_result(bool exp, bool res);
static void	putsuccess(char *filename);

int	main(void)
{
	bool	result;

	result = false;

	char *unclosed_map[] = {
		"",
		"",
		"",
		"",
		"    1111111111111111111111111",
		"    1000000000110000000000001",
		"    1011000001110000000000001",
		"    1001000000000000000000001",
		"    111111111011000001110000000000001",
		"    100000000011000001110111101111111",
		"    1111011111 111011100000010001",
		"    11110111111111011101010010001",
		"    11000000110101011100000010001",
		"    10000000000000001100000010001",
		"    10000000000000001101010010001",
		"    11000001110101011111011110N0111",
		"    11110111 1110101 101111010001",
		"    11111111 1111111 111111111111",
		NULL
	};

	char testname[] = "Unclosed map";
	bool exp_res = false;
	bool response = is_closed(unclosed_map, 19);
	result = response == exp_res;

	if (result)
		putsuccess(testname);
	else
	{
		puterror(testname);
		unexpected_result(exp_res, result);
	}

	if (result)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}


static void	puterror(char *filename)
{
	dprintf(STDERR_FILENO, "\nThe test: %s - was failed:\n", filename);
}

static void unexpected_result(bool exp, bool res)
{
	dprintf(STDERR_FILENO, "The expected result: %d; yours: %d\n", exp, res);
}

static void	putsuccess(char *filename) {
	printf("Test: %s - passed!\n", filename);
}
