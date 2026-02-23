/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_trim_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:25:49 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/23 17:48:41 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	base_case(char **exp_arr, char **input, int height, char *test_name);
static bool	compare_str_arrays(char **arr1, char **arr2);
static void	puterror(char *filename);
static void	putsuccess(char *filename);
static void	print_str_array(char **arr);


int	main(void)
{
	bool	result;

	char *bgl1  = malloc(ft_strlen("         ") + 1);
	char *bgl2  = malloc(ft_strlen("   1111111 ") + 1);
	char *bgl3  = malloc(ft_strlen("   1000001 ") + 1);
	char *bgl4  = malloc(ft_strlen("   1011101   ") + 1);
	char *bgl5  = malloc(ft_strlen("   101 101    ") + 1);
	char *bgl6  = malloc(ft_strlen("   1011101   ") + 1);
	char *bgl7  = malloc(ft_strlen("   1000001     ") + 1);
	char *bgl8  = malloc(ft_strlen("   1111111 ") + 1);
	char *bgl9  = malloc(ft_strlen("       ") + 1);
	char *bgl10 = malloc(ft_strlen(" ") + 1);

	if (!bgl1 || !bgl2 || !bgl3 || !bgl4 || !bgl5 ||
		!bgl6 || !bgl7 || !bgl8 || !bgl9 || !bgl10)
		return (1);

	ft_strlcpy(bgl1,  "         ", ft_strlen("         ") + 1);
	ft_strlcpy(bgl2,  "   1111111 ", ft_strlen("   1111111 ") + 1);
	ft_strlcpy(bgl3,  "   1000001 ", ft_strlen("   1000001 ") + 1);
	ft_strlcpy(bgl4,  "   1011101   ", ft_strlen("   1011101   ") + 1);
	ft_strlcpy(bgl5,  "   101 101    ", ft_strlen("   101 101    ") + 1);
	ft_strlcpy(bgl6,  "   1011101   ", ft_strlen("   1011101   ") + 1);
	ft_strlcpy(bgl7,  "   1000001     ", ft_strlen("   1000001     ") + 1);
	ft_strlcpy(bgl8,  "   1111111 ", ft_strlen("   1111111 ") + 1);
	ft_strlcpy(bgl9,  "       ", ft_strlen("       ") + 1);
	ft_strlcpy(bgl10, " ", ft_strlen(" ") + 1);

	char *bagel[] = {
		bgl1, bgl2, bgl3,
		bgl4, bgl5, bgl6,
		bgl7, bgl8, bgl9,
		bgl10, NULL
	};

	char *exp_bagel[] = {
		"1111111",
		"1000001",
		"1011101",
		"101 101",
		"1011101",
		"1000001",
		"1111111",
		NULL
	};

	result = base_case(exp_bagel, bagel, 10, "Bagel case");

	for (int i = 0; bagel[i]; i++)
		free(bagel[i]);

	if (result)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static bool	base_case(char **exp_arr, char **input, int height, char *test_name)
{
	t_map	map;

	map.data = input;
	map.height = height;
	trim_map(&map);

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
