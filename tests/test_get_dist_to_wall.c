/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_dist_to_wall.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/09 00:00:00 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

# define DIST_EPS 1e-4f

typedef struct s_dist_case
{
	const char	*name;
	t_coords	origin;
	t_coords	wall;
	float		expected;
}	t_dist_case;

static bool	approx_eq(float a, float b)
{
	return (fabsf(a - b) < DIST_EPS);
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
	** get_dist_to_wall computes Euclidean distance between two points.
	** Float results are compared with epsilon 1e-4 to handle precision.
	*/
	static const t_dist_case	cases[] = {
		{"3-4-5 right triangle",
			{0.0f, 0.0f}, {3.0f, 4.0f}, 5.0f},
		{"same point -> zero distance",
			{1.0f, 1.0f}, {1.0f, 1.0f}, 0.0f},
		{"horizontal line",
			{0.0f, 0.0f}, {5.0f, 0.0f}, 5.0f},
		{"vertical line",
			{0.0f, 0.0f}, {0.0f, 3.0f}, 3.0f},
		{"fractional coords vertical",
			{1.5f, 1.5f}, {1.5f, 3.5f}, 2.0f},
		{"negative direction uses abs value",
			{5.0f, 5.0f}, {2.0f, 1.0f}, 5.0f},
		{"unit diagonal",
			{0.0f, 0.0f}, {0.5f, 0.5f}, sqrtf(0.5f)},
	};
	size_t	total;
	size_t	passed;
	float	result;
	size_t	i;

	total = sizeof(cases) / sizeof(cases[0]);
	passed = 0;
	i = 0;
	while (i < total)
	{
		result = get_dist_to_wall(cases[i].origin, cases[i].wall);
		if (approx_eq(result, cases[i].expected))
		{
			putsuccess(cases[i].name);
			passed++;
		}
		else
		{
			puterror(cases[i].name);
			dprintf(STDERR_FILENO, "  expected %.6f, got %.6f\n",
				cases[i].expected, result);
		}
		i++;
	}
	if (passed == total)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
