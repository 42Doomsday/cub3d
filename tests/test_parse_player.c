/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:20:00 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/18 16:51:05 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	simple_test(void);
static bool	bad_map_test(void);
static bool	duplicated_player_test(void);
static void	puterror(char *filename);
static void	putsuccess(char *filename);

int	main(void)
{
	bool result = simple_test();
	result &= bad_map_test();
	result &= duplicated_player_test();
	if (result)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static bool	simple_test(void)
{
	t_player	player;
	ft_bzero(&player, sizeof(player));
	char	*map[] = {
		"1111111",
		"10000N1",
		"1000001",
		"1111111",
		NULL
	};
	parse_player(map, &player);
	if (player.x == 5 && player.y == 1 && player.side == 'N')
	{
		putsuccess("Simple map");
		return (true);
	}
	else
	{
		puterror("Simple map");
		return (false);
	}
}

static bool	bad_map_test(void)
{
	t_player	player;
	ft_bzero(&player, sizeof(player));
	char	*map[] = {
		"1111111",
		"1000001",
		"1000001",
		"1111111",
		NULL
	};
	parse_player(map, &player);
	if (player.x == 0 && player.y == 0 && player.side == 0)
	{
		putsuccess("Bad map test");
		return (true);
	}
	else
	{
		puterror("Bad map test");
		return (false);
	}
}

static bool	duplicated_player_test(void)
{
	t_player	player;
	ft_bzero(&player, sizeof(player));
	char	*map[] = {
		"1111111",
		"1E00001",
		"100N001",
		"1111111",
		NULL
	};
	bool result = parse_player(map, &player);
	if (result == false)
	{
		putsuccess("Duplicated player test");
		return (true);
	}
	else
	{
		puterror("Duplicated player test");
		return (false);
	}
}

static void	puterror(char *filename)
{
	dprintf(STDERR_FILENO, "\nThe test: %s - was failed:\n", filename);
}

static void	putsuccess(char *filename)
{
	printf("Test: %s - passed!\n", filename);
}
