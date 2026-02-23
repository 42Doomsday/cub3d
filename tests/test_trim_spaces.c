/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_trim_spaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:33:43 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/23 14:58:28 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	compare_str_arrays(char **arr1, char **arr2);
static void	puterror(char *filename);
static void	putsuccess(char *filename);
static void	print_str_array(char **arr);

int	main(void)
{

	char	line1[] = " First ";
	char	line2[] = "  Second  ";
	char	line3[] = "   Third   ";
	char	*map_lines[] = {line1, line2, line3, NULL};

	t_map	map;
	map.data = map_lines;
	map.height = 3;
	map.width = 12;

	trim_spaces(&map);

	char	*expected_map_lines[] = {
		"First ",
		" Second",
		"  Third",
		NULL
	};

	bool result = compare_str_arrays(expected_map_lines, map_lines);
	char test_name[] = "Simple Trim";
	if (result)
	{
		putsuccess(test_name);
		return (EXIT_SUCCESS);
	}
	else
	{
		puterror(test_name);
		printf("Expected map:\n");
		print_str_array(expected_map_lines);
		printf("Your's map:\n");
		print_str_array(map_lines);
		return (EXIT_FAILURE);
	}
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
