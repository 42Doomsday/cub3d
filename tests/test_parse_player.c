/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:20:00 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/16 17:35:18 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	simple_test(void);
static void	bad_map_test(void);
static void	duplicated_player_test(void);
static void	puterror(char *filename);
static void	putsuccess(char *filename);

int	main(void)
{
	simple_test();
	bad_map_test();
	duplicated_player_test();
	return (EXIT_SUCCESS);
}

static void	simple_test(void)
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
		putsuccess("Simple map");
	else
		puterror("Simple map");
}

static void	bad_map_test(void)
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
		putsuccess("Bad map test");
	else
		puterror("Bad map test");
}

static void	duplicated_player_test(void)
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
		putsuccess("Duplicated player test");
	else
		puterror("Duplicated player test");
}

static void	puterror(char *filename)
{
	dprintf(STDERR_FILENO, "\nThe test: %s - was failed:\n", filename);
}

static void	putsuccess(char *filename)
{
	printf("Test: %s - passed!\n", filename);
}
