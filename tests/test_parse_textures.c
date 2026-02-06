/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 11:57:51 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/06 12:04:16 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

# define TEXTURES_TESTS_PATH "tests/examples/textures/"

static void	check_invalid(char **invalid_files, bool expected_result);
static void	check_valid(char **valid_files, bool expected_result);
static void	add_prefix(char **in, char *prefix);
static int	get_test_file(char *filename);
static void	puterror(char *filename);
static void unexpected_result(bool exp, bool res);
static void	putsuccess(char *filename);
static void	free_struct(textures_t *textures);
static bool	is_not_empty(textures_t *textures);

int	main(void)
{
	char *invalid_test_files[] = {
		"duplicated",
		"empty",
		"extra_lines",
		"incomplete_colors",
		"incomplete_floor",
		"incomplete_sides",
		"incomplete_texture_path",
		"new_lines_only",
		"wrong_key",
		NULL
	};

	add_prefix(invalid_test_files, "invalid/");

	char *valid_test_files[] = {
		"line_separated",
		"mixed",
		"more_spaces",
		"normal",
		"path_with_space",
		NULL
	};

	add_prefix(valid_test_files, "valid/");

	check_invalid(invalid_test_files, false);
	for (int i = 0; invalid_test_files[i] != NULL; i++)
		free(invalid_test_files[i]);

	check_valid(valid_test_files, true);
	for (int i = 0; valid_test_files[i] != NULL; i++)
		free(valid_test_files[i]);

	return (EXIT_SUCCESS);
}

static void	check_invalid(char **invalid_files, bool expected_result)
{
	textures_t	textures;
	int			fd;
	bool		result;

	for (int i = 0; invalid_files[i] != NULL; i++)
	{
		ft_bzero(&textures, sizeof(textures_t));
		fd = get_test_file(invalid_files[i]);
		result = parse_textures(fd, &textures);
		if (result != expected_result)
		{
			puterror(invalid_files[i]);
			unexpected_result(expected_result, result);
		}
		else
			putsuccess(invalid_files[i]);
		if (fd > -1)
			close(fd);
		free_struct(&textures);
	}
}

static void	check_valid(char **valid_files, bool expected_result)
{
	textures_t	textures;
	int			fd;
	bool		result;

	for (int i = 0; valid_files[i] != NULL; i++)
	{
		ft_bzero(&textures, sizeof(textures_t));
		fd = get_test_file(valid_files[i]);
		result = parse_textures(fd, &textures);
		if (result == expected_result)
		{
			if (is_not_empty(&textures))
				putsuccess(valid_files[i]);
			else
			{
				puterror(valid_files[i]);
				ft_putstr_fd("The structure is not filled\n", 2);
			}
		}
		else
		{
			puterror(valid_files[i]);
			unexpected_result(expected_result, result);
		}
		if (fd > -1)
			close(fd);
		free_struct(&textures);
	}
}

static void	add_prefix(char **in, char *prefix)
{
	for (int i = 0; in[i] != NULL; i++) {
		in[i] = ft_strjoin(prefix, in[i]);
	}
}

static int	get_test_file(char *filename)
{
	char	*path;
	int		fd;

	path = ft_strjoin(TEXTURES_TESTS_PATH, filename);
	fd = open(path, O_RDONLY);
	free(path);
	return (fd);
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

static void	free_struct(textures_t *textures)
{
	free(textures->east);
	free(textures->north);
	free(textures->south);
	free(textures->west);
	free(textures->floor);
	free(textures->ceiling);
}

static bool	is_not_empty(textures_t *textures)
{
	return (
		textures->ceiling &&
		textures->east &&
		textures->floor &&
		textures->north &&
		textures->south &&
		textures->west
	);
}

