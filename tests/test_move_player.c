/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_move_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/09 00:00:00 by dkalgano        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

# define MOVE_EPS 1e-4f

/*
** Map (6x6 closed room):
**   111111   y=0
**   100001   y=1
**   100001   y=2
**   100001   y=3
**   100001   y=4
**   111111   y=5
**
** Open cells: x in [1..4], y in [1..4]
** Wall columns/rows: x in {0,5}, y in {0,5}
**
** PLAYER_STEP = 5, PLAYER_HITBOX_R = 0.3
** delta = 0.1  →  raw displacement = 5 * 0.1 = 0.5 per axis
**
** Degree semantics for move_player(world, degree, delta):
**   degree passed to convert_degree_to_radians() then added to
**   player->dir.radians.  A W-key press sends degree=90, which
**   evaluates to radians=(90-90)*PI/180=0, so the player moves
**   exactly along their facing direction.
**
** Facing East (update_player_degree 90):  dir.radians=0, unit=(1,0)
** Facing North (update_player_degree 0):  dir.radians=PI/2, unit=(0,-1)
** Facing South (update_player_degree 180): dir.radians=-PI/2, unit=(0,1)
*/

typedef struct s_move_case
{
	const char	*name;
	float		dir_deg;   /* player facing direction (degrees) */
	t_coords	start;     /* player starting position */
	float		move_deg;  /* move_player "degree" argument    */
	double		delta;
	bool		check_x;   /* true=check x, false=check y      */
	float		expected;  /* expected coordinate value        */
}	t_move_case;

static void	puterror(const char *name)
{
	dprintf(STDERR_FILENO, "\nThe test: %s - was failed:\n", name);
}

static void	putsuccess(const char *name)
{
	printf("Test: %s - passed!\n", name);
}

int	main(void)
{
	/*
	** W-key = degree 90  (move in player's exact facing direction)
	** S-key = degree 270 (move opposite to facing direction)
	**
	** Cases:
	** 1. Facing East, move forward (+x): x goes 2.5 → 3.0
	** 2. Facing East, move forward into east wall: x clamped to 4.7
	**    (player at 4.5, new_x=5.0, tile_x=5 is wall → 5 - 0.3 = 4.7)
	** 3. Facing East, move backward (-x) into west wall: x clamped to 1.3
	**    (player at 1.5, new_x=1.0, tile_x=0 is wall → 0+1+0.3 = 1.3)
	** 4. Facing North, move forward (-y): y goes 2.5 → 2.0
	** 5. Facing North, move forward into north wall: y clamped to 1.3
	**    (player at 1.5, new_y=1.0, tile_y=0 is wall → 0+1+0.3 = 1.3)
	** 6. Facing South, move forward (+y) into south wall: y clamped to 4.7
	**    (player at 4.5, new_y=5.0, tile_y=5 is wall → 5 - 0.3 = 4.7)
	*/
	static const t_move_case	cases[] = {
		{"east open (+x): 2.5→3.0",      90,  {2.5f, 2.5f},  90, 0.1, true,  3.0f},
		{"east clamped at east wall",     90,  {4.5f, 2.5f},  90, 0.1, true,  4.7f},
		{"east clamped at west wall",     90,  {1.5f, 2.5f}, 270, 0.1, true,  1.3f},
		{"north open (-y): 2.5→2.0",      0,  {2.5f, 2.5f},  90, 0.1, false, 2.0f},
		{"north clamped at north wall",    0,  {2.5f, 1.5f},  90, 0.1, false, 1.3f},
		{"south clamped at south wall",  180,  {2.5f, 4.5f},  90, 0.1, false, 4.7f},
	};
	char	*rows[] = {
		"111111",
		"100001",
		"100001",
		"100001",
		"100001",
		"111111",
		NULL
	};
	t_map		map;
	t_player	player;
	t_world		world;
	size_t		total;
	size_t		passed;
	float		got;
	size_t		i;

	map.data = rows;
	map.height = 6;
	map.width = 6;
	world.map = &map;
	world.player = &player;
	total = sizeof(cases) / sizeof(cases[0]);
	passed = 0;
	i = 0;
	while (i < total)
	{
		update_player_degree(&player, cases[i].dir_deg);
		player.coords = cases[i].start;
		move_player(&world, cases[i].move_deg, cases[i].delta);
		if (cases[i].check_x)
			got = player.coords.x;
		else
			got = player.coords.y;
		if (fabsf(got - cases[i].expected) < MOVE_EPS)
		{
			putsuccess(cases[i].name);
			passed++;
		}
		else
		{
			puterror(cases[i].name);
			dprintf(STDERR_FILENO, "  expected %.4f, got %.4f\n",
				cases[i].expected, got);
		}
		i++;
	}
	if (passed == total)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
