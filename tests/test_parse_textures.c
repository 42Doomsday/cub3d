/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 11:57:51 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/05 16:03:51 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

// valgrind --track-fds=yes --leak-check=full --error-exitcode=1 ./a.out

static void puterror(char *filename, bool result, bool expected) {
	int	stdout_fd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("The test: %s - was failed:\n", filename);
	printf("Expected result: %d; yours: %d\n", expected, result);
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdout_fd);
}

static void putsuccess(char *filename) {
	printf("Test: %s - passed!\n", filename);
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
	for (int i = 0; invalid_test_files[i] != NULL; i++) {
		textures_t	textures;
		char *filename = ft_strjoin("tests/examples/textures/invalid/", invalid_test_files[i]);
		int fd = open(filename, O_RDONLY);
		bool result = parse_textures(fd, &textures);
		if (result == true)
			puterror(invalid_test_files[i], result, false);
		else
			putsuccess(invalid_test_files[i]);
		close(fd);
		free(filename);
	}
	return (EXIT_SUCCESS);
}
