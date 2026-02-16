/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_tabs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:54:05 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/16 17:15:38 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	test_case(char *input, char *exp_result);
static void	puterror(char *filename);
static void	unexpected_result(char *exp, char *res);
static void	putsuccess(char *filename);

int	main(void)
{
	test_case(NULL, NULL);
	test_case("Nothing", "Nothing");
	test_case("One	Tab", "One    Tab");
	test_case("More	Tabs	Here", "More    Tabs    Here");
	return (EXIT_SUCCESS);
}

static bool	test_case(char *input, char *exp_result)
{
	size_t	size;
	char	*test_line;
	t_list	*test_node;
	t_list	*new_node;
	char	*new_line;
	bool	result;

	test_node = NULL;
	if (input)
	{
		size = ft_strlen(input) + 1;
		test_line = malloc(size);
		ft_memcpy(test_line, input, size);
		test_node = ft_lstnew(test_line);
	}

	result = false;
	new_node = expand_tabs(test_node);
	if (new_node)
	{
		new_line = new_node->content;
		if (ft_strncmp(new_line, exp_result, size) == 0)
		{
			putsuccess(input);
			result = true;
		}
		else
		{
			puterror(input);
			unexpected_result(exp_result, new_line);
		}
		free(new_line);
		free(test_node);
	}
	if (input == NULL && new_node == NULL)
	{
		putsuccess(input);
		result = true;
	}
	return (result);
}

static void	puterror(char *filename)
{
	dprintf(STDERR_FILENO, "\nThe test: %s - was failed:\n", filename);
}

static void unexpected_result(char *exp, char *res)
{
	dprintf(STDERR_FILENO, "The expected result: %s; yours: %s\n", exp, res);
}

static void	putsuccess(char *filename)
{
	printf("Test: %s - passed!\n", filename);
}
