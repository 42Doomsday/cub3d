/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_flood_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:37:41 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/20 17:11:20 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	compare_str_arrays(char **arr1, char **arr2);
static void	puterror(char *filename);
static void	putsuccess(char *filename);
static void	print_str_array(char **arr);

int	main(void)
{
	bool	result;
	char	row1[] = "111111";
	char	row2[] = "100N01";
	char	row3[] = "111111";

	char	*input_map[] = {row1, row2, row3, NULL};

	char	*expected_map[] = {
		"222222",
		"222222",
		"222221",
		NULL
	};

	result = flood_fill(input_map, 0, 0);
	result &= compare_str_arrays(expected_map, input_map);



	if (result)
	{
		putsuccess("Basic flood fill");
		return (EXIT_SUCCESS);
	}

	puterror("Basic flood fill");
	dprintf(STDERR_FILENO, "Maps are different\n");
	print_str_array(input_map);
	print_str_array(expected_map);
	return (EXIT_FAILURE);
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
