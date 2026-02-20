/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_read_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:36:29 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/20 17:17:43 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	compare_str_arrays(char **arr1, char **arr2);
static void	puterror(char *filename);
static void	putsuccess(char *filename);
static void	print_str_array(char **arr);

int	main(void)
{

	int fd = open("tests/examples/map/valid/bagel", O_RDONLY);
	char *exp_res[] = {
		"",
		"",
		"",
		"",
		"         11111111111111",
		"         1000000E000001",
		"         10001111110001",
		"         10001    10001",
		"         10001111110001",
		"         10000000000001",
		"         11111111111111",
		"",
		"",
		"",
		NULL
	};

	char **res = read_lines(fd);
	bool result = compare_str_arrays(exp_res, res);
	if (result)
		putsuccess("Bagel");
	else
	{
		puterror("Bagel");
		printf("Yours:\n");
		print_str_array(res);
		printf("Expected:\n");
		print_str_array(exp_res);
	}

	int	idx = 0;
	while (res[idx])
		free(res[idx++]);
	free(res);

	if (result)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static bool	compare_str_arrays(char **arr1, char **arr2)
{
	int	idx;

	idx = 0;
	while (arr1 && arr1[idx])
	{
		if (ft_strncmp(arr1[idx], arr2[idx], ft_strlen(arr1[idx]) + 1) > 0)
			return (false);
		idx++;
	}
	return (true);
}

static void	puterror(char *filename)
{
	dprintf(STDERR_FILENO, "\nThe test: %s - was failed:\n", filename);
}

static void	putsuccess(char *filename)
{
	printf("Test: %s - passed!\n", filename);
}


static void	print_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
	printf("\n");
}
