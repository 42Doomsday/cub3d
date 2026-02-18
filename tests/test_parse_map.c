/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:38:24 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/13 17:08:07 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

# define TEXTURES_TESTS_PATH "tests/examples/map/"

static void	check_invalid(char **invalid_files, bool expected_result);
static void	check_valid(char **valid_files, bool expected_result);
static void	add_prefix(char **in, char *prefix);
static int	get_test_file(char *filename);
static void	puterror(char *filename);
static void unexpected_result(bool exp, bool res);
static void	putsuccess(char *filename);
static bool	is_not_empty_player(t_player *player);
static bool	is_not_empty_map(t_map *map);

int	main(void)
{
	char *invalid_test_files[] = {
		"duplicated_map",
		"duplicated_player",
		"empty",
		"extra_character",
		"new_lines",
		"open",
		NULL
	};

	add_prefix(invalid_test_files, "invalid/");

	char *valid_test_files[] = {
		"bagel",
		"curved",
		"normal",
		"small",
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
	t_player	player;
	t_map		map;
	int			fd;
	bool		result;

	for (int i = 0; invalid_files[i] != NULL; i++)
	{
		ft_bzero(&player, sizeof(t_player));
		ft_bzero(&map, sizeof(t_map));
		fd = get_test_file(invalid_files[i]);
		result = parse_map(fd, &map, &player);
		if (result != expected_result)
		{
			puterror(invalid_files[i]);
			unexpected_result(expected_result, result);
		}
		else
			putsuccess(invalid_files[i]);
		if (fd > -1)
			close(fd);
		free_map(&map);
	}
}

static void	check_valid(char **valid_files, bool expected_result)
{
	t_player	player;
	t_map		map;
	int			fd;
	bool		result;

	for (int i = 0; valid_files[i] != NULL; i++)
	{
		ft_bzero(&player, sizeof(t_player));
		ft_bzero(&map, sizeof(t_map));
		fd = get_test_file(valid_files[i]);
		result = parse_map(fd, &map, &player);
		if (result == expected_result)
		{
			if (is_not_empty_map(&map) && is_not_empty_player(&player))
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
		free_map(&map);
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

static bool	is_not_empty_map(t_map *map)
{
	return (
		map->data &&
		map->height &&
		map->width
	);
}

static bool	is_not_empty_player(t_player *player)
{
	return (
		player->side &&
		player->x &&
		player->y
	);
}
