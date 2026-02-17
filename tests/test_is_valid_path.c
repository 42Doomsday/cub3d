/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_valid_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 12:28:54 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/17 17:10:35 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define TEST_PATH "tests/examples/path/"

static int	get_test_file(char *filename);
static void	puterror(char *filename);
static void unexpected_result(bool exp, bool res);
static void	putsuccess(char *filename);
static void	run_test(int fd, bool exp_res);
static void	delete_newline(char *line);

int	main(void)
{
	int	fd;

	fd = get_test_file("valid");
	run_test(fd, true);
	close (fd);

	fd = get_test_file("invalid");
	run_test(fd, false);
	close(fd);

	return (EXIT_SUCCESS);
}

static void	run_test(int fd, bool exp_res)
{
	char	*line;
	bool	result;

	while ((line = get_next_line(fd)) != NULL)
	{
		line[ft_strlen(line) - 1] = '\0';
		result = is_valid_path(line);
		if (result != exp_res)
		{
			puterror(line);
			unexpected_result(exp_res, result);
		}
		else
			putsuccess(line);
		free(line);
	}
	close(fd);
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
