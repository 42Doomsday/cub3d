/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_trim_spaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:33:43 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/23 17:17:44 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	base_case(char **exp_arr, char **input, char *test_name);
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

	char	*expected_map_lines[] = {
		"First ",
		" Second",
		"  Third",
		NULL
	};

	char bad_align_line1[] = " a    ";
	char bad_align_line2[] = "  bbbbbbbbbbbbbbb  ";
	char bad_align_line3[] = "   cccccccccccccccccccccccccccccccccccccc  ";

	char *bad_align_map[] = {bad_align_line1, bad_align_line2, bad_align_line3, NULL};

	char *exp_for_bad_align_map[] = {
		"a    ",
		" bbbbbbbbbbbbbbb  ",
		"  cccccccccccccccccccccccccccccccccccccc",
		NULL
	};

	bool result = base_case(expected_map_lines, map_lines, "Simple trim");
	result &= base_case(NULL, NULL, "Null map");
	result &= base_case(exp_for_bad_align_map, bad_align_map, "Different size lines");


	if (result)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static bool	base_case(char **exp_arr, char **input, char *test_name)
{
	t_map	map;

	map.data = input;
	trim_spaces(&map);

	bool result = compare_str_arrays(exp_arr, input);

	if (result)
		putsuccess(test_name);
	else
	{
		puterror(test_name);
		printf("Expected map:\n");
		print_str_array(exp_arr);
		printf("Your's map:\n");
		print_str_array(input);
	}
	return (result);
}

static bool	compare_str_arrays(char **arr1, char **arr2)
{
	int	idx;

	idx = 0;
	while (arr1 && arr1[idx])
	{
		if (ft_strlen(arr1[idx]) != ft_strlen(arr2[idx]))
			return (false);
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
		printf("size: %zu\n", ft_strlen(arr[i]));
		i++;
	}
	printf("\n");
}
