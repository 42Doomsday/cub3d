/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_valid_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 12:28:54 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/18 16:40:50 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define TEST_PATH "tests/examples/path/"

static int	get_test_file(char *filename);
static void	puterror(char *filename);
static void unexpected_result(bool exp, bool res);
static void	putsuccess(char *filename);
static bool	run_test(int fd, bool exp_res);
static void	delete_newline(char *line);

int	main(void)
{
	int	fd;
	bool	result;

	result = true;

	fd = get_test_file("valid");
	result &= run_test(fd, true);
	close (fd);

	fd = get_test_file("invalid");
	result &= run_test(fd, false);
	close(fd);

	if (result)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static bool	run_test(int fd, bool exp_res)
{
	char	*line;
	bool	result;
	bool	test_result;

	while ((line = get_next_line(fd)) != NULL)
	{
		result = is_valid_path(line);
		test_result = result == exp_res;
		if (test_result)
			putsuccess(line);
		else
		{
			puterror(line);
			unexpected_result(exp_res, result);
		}
		free(line);
	}
	close(fd);
	return (test_result);
}

static void	puterror(char *filename)
{
	delete_newline(filename);
	dprintf(STDERR_FILENO, "\nThe test: %s - was failed:\n", filename);
}

static void unexpected_result(bool exp, bool res)
{
	dprintf(STDERR_FILENO, "The expected result: %d; yours: %d\n", exp, res);
}

static void	putsuccess(char *filename)
{
	delete_newline(filename);
	printf("Test: %s - passed!\n", filename);
}

static void	delete_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static int	get_test_file(char *filename)
{
	char	*path;
	int		fd;

	path = ft_strjoin(TEST_PATH, filename);
	fd = open(path, O_RDONLY);
	free(path);
	return (fd);
}
