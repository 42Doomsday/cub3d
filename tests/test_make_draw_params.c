/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_make_draw_params.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/09 00:00:00 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include <math.h>

# define DRAW_EPS 1e-4f

typedef struct s_draw_params_case
{
	const char	*name;
	t_coords	player_coords;
	int			bs;
	int			exp_cx;
	int			exp_cy;
	float		exp_start_x;
	float		exp_start_y;
	int			exp_radius;
}	t_draw_params_case;

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
	** make_draw_params maps player world coords → pixel coords:
	**   center.x = (int)(coords.x * bs)
	**   center.y = (int)(coords.y * bs)
	**   radius   = bs / 4
	**   start_px = coords * bs  (float, for line drawing origin)
	*/
	static const t_draw_params_case	cases[] = {
		{"(1.5,2.5) bs=8: center=(12,20)",
			{1.5f, 2.5f}, 8, 12, 20, 12.0f, 20.0f, 2},
		{"(3.0,3.0) bs=10: center=(30,30)",
			{3.0f, 3.0f}, 10, 30, 30, 30.0f, 30.0f, 2},
		{"(0.5,0.5) bs=16: center=(8,8), radius=4",
			{0.5f, 0.5f}, 16, 8, 8, 8.0f, 8.0f, 4},
		{"(2.0,4.0) bs=12: center=(24,48)",
			{2.0f, 4.0f}, 12, 24, 48, 24.0f, 48.0f, 3},
	};
	t_player		player;
	t_player_draw	result;
	size_t			total;
	size_t			passed;
	bool			ok;
	size_t			i;

	total = sizeof(cases) / sizeof(cases[0]);
	passed = 0;
	i = 0;
	while (i < total)
	{
		ft_memset(&player, 0, sizeof(player));
		player.coords = cases[i].player_coords;
		result = make_draw_params(&player, cases[i].bs);
		ok = (result.center.x == cases[i].exp_cx
				&& result.center.y == cases[i].exp_cy
				&& result.radius == cases[i].exp_radius
				&& fabsf(result.start_px.x - cases[i].exp_start_x) < DRAW_EPS
				&& fabsf(result.start_px.y - cases[i].exp_start_y) < DRAW_EPS);
		if (ok)
		{
			putsuccess(cases[i].name);
			passed++;
		}
		else
		{
			puterror(cases[i].name);
			dprintf(STDERR_FILENO,
				"  center expected (%d,%d) got (%d,%d)\n",
				cases[i].exp_cx, cases[i].exp_cy,
				result.center.x, result.center.y);
			dprintf(STDERR_FILENO,
				"  radius expected %d got %d\n",
				cases[i].exp_radius, result.radius);
			dprintf(STDERR_FILENO,
				"  start_px expected (%.4f,%.4f) got (%.4f,%.4f)\n",
				cases[i].exp_start_x, cases[i].exp_start_y,
				result.start_px.x, result.start_px.y);
		}
		i++;
	}
	if (passed == total)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
