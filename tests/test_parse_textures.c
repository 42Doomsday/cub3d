/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 11:57:51 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/05 16:22:36 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

# define TEXTURES_TESTS_PATH "tests/examples/textures/invalid/"

static int	get_test_file(char *filename)
{
	char	*path;
	int		fd;

	path = ft_strjoin(TEXTURES_TESTS_PATH, filename);
	fd = open(filename, O_RDONLY);
	free(path);
	return (fd);
}

static void	puterror(char *filename, bool result, bool expected)
{
	int	stdout_fd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("\nThe test: %s - was failed:\n", filename);
	printf("Expected result: %d; yours: %d\n", expected, result);
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdout_fd);
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

	textures_t	textures;
	int			fd;
	bool		result;

	for (int i = 0; invalid_test_files[i] != NULL; i++)
	{
		ft_bzero(&textures, sizeof(textures_t));
		fd = get_test_file(invalid_test_files[i]);
		result = parse_textures(fd, &textures);
		if (result == true)
			puterror(invalid_test_files[i], result, false);
		else
			putsuccess(invalid_test_files[i]);
		if (fd > -1)
			close(fd);
		free_struct(&textures);
	}
	return (EXIT_SUCCESS);
}
