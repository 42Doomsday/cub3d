/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_side_of_wall.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/09 00:00:00 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_side_case
{
	const char		*name;
	t_coords		wall;
	t_vec2			dir;
	t_texture_id	expected;
}	t_side_case;

static const char	*texture_id_name(t_texture_id id)
{
	static const char	*names[] = {"NORTH", "SOUTH", "EAST", "WEST",
		"FLOOR", "CEILING"};

	if (id < T_COUNT)
		return (names[id]);
	return ("UNKNOWN");
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
	** Wall on a vertical grid line (x integer, y not) → EAST or WEST.
	** Wall on a horizontal grid line (y integer, x not) → NORTH or SOUTH.
	** A diagonal ray resolves to whichever axis it crossed last.
	*/
	static const t_side_case	cases[] = {
		{"vertical wall, ray east -> EAST",
			{3.0f, 1.5f}, { 1.0f,  0.0f}, EAST},
		{"vertical wall, ray west -> WEST",
			{3.0f, 1.5f}, {-1.0f,  0.0f}, WEST},
		{"horizontal wall, ray south -> SOUTH",
			{1.5f, 3.0f}, { 0.0f,  1.0f}, SOUTH},
		{"horizontal wall, ray north -> NORTH",
			{1.5f, 3.0f}, { 0.0f, -1.0f}, NORTH},
		{"diagonal ray hits vertical wall -> EAST",
			{4.0f, 2.5f}, { 0.7f,  0.7f}, EAST},
		{"diagonal ray hits horizontal wall -> SOUTH",
			{2.5f, 4.0f}, { 0.7f,  0.7f}, SOUTH},
	};
	size_t			total;
	size_t			passed;
	t_texture_id	result;
	size_t			i;

	total = sizeof(cases) / sizeof(cases[0]);
	passed = 0;
	i = 0;
	while (i < total)
	{
		result = get_side_of_wall(cases[i].wall, cases[i].dir);
		if (result == cases[i].expected)
		{
			putsuccess(cases[i].name);
			passed++;
		}
		else
		{
			puterror(cases[i].name);
			dprintf(STDERR_FILENO, "  expected %s, got %s\n",
				texture_id_name(cases[i].expected), texture_id_name(result));
		}
		i++;
	}
	if (passed == total)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
