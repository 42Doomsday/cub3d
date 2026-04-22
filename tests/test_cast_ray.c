/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cast_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/09 00:00:00 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

# define CAST_EPS 1e-4f

typedef struct s_cast_case
{
	const char	*name;
	t_coords	origin;
	t_vec2		dir;
	t_coords	expected_wall;
}	t_cast_case;

static bool	coords_approx_eq(t_coords a, t_coords b)
{
	return (fabsf(a.x - b.x) < CAST_EPS && fabsf(a.y - b.y) < CAST_EPS);
}

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
	** Map (5x5 closed room):
	**   11111   (y=0)
	**   10001   (y=1)
	**   10001   (y=2)
	**   10001   (y=3)
	**   11111   (y=4)
	**
	** Player at (2.5, 2.5). Cardinal rays each travel 1.5 units to the
	** nearest wall face. Expected hit points verified by hand-tracing
	** the DDA loop in cast_ray.c.
	*/
	char	*rows[] = {
		"11111",
		"10001",
		"10001",
		"10001",
		"11111",
		NULL
	};
	t_map			map;
	static const t_cast_case	cases[] = {
		{"east  {1,0}  center",   {2.5f, 2.5f}, { 1.0f,  0.0f}, {4.0f, 2.5f}},
		{"west  {-1,0} center",   {2.5f, 2.5f}, {-1.0f,  0.0f}, {1.0f, 2.5f}},
		{"south {0,1}  center",   {2.5f, 2.5f}, { 0.0f,  1.0f}, {2.5f, 4.0f}},
		{"north {0,-1} center",   {2.5f, 2.5f}, { 0.0f, -1.0f}, {2.5f, 1.0f}},
		{"east  {1,0}  from (1.5,1.5)", {1.5f, 1.5f}, {1.0f, 0.0f}, {4.0f, 1.5f}},
		{"south {0,1}  from (1.5,1.5)", {1.5f, 1.5f}, {0.0f, 1.0f}, {1.5f, 4.0f}},
	};
	size_t		total;
	size_t		passed;
	t_coords	result;
	size_t		i;

	map.data = rows;
	map.height = 5;
	map.width = 5;
	total = sizeof(cases) / sizeof(cases[0]);
	passed = 0;
	i = 0;
	while (i < total)
	{
		result = cast_ray_to_wall(cases[i].origin, cases[i].dir, &map);
		if (coords_approx_eq(result, cases[i].expected_wall))
		{
			putsuccess(cases[i].name);
			passed++;
		}
		else
		{
			puterror(cases[i].name);
			dprintf(STDERR_FILENO,
				"  expected (%.4f, %.4f), got (%.4f, %.4f)\n",
				cases[i].expected_wall.x, cases[i].expected_wall.y,
				result.x, result.y);
		}
		i++;
	}
	if (passed == total)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
