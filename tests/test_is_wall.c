/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/09 00:00:00 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_wall_coord_case
{
	const char	*name;
	int			x;
	int			y;
	bool		expected;
}	t_wall_coord_case;

typedef struct s_is_wall_case
{
	const char	*name;
	t_coords	start;
	t_vec2		dir;
	bool		expected;
}	t_is_wall_case;

static void	puterror(const char *name)
{
	dprintf(STDERR_FILENO, "\nThe test: %s - was failed:\n", name);
}

static void	putsuccess(const char *name)
{
	printf("Test: %s - passed!\n", name);
}

static int	run_coord_cases(t_map *map)
{
	/*
	** Map (5x5):
	**   11111
	**   10001
	**   10001
	**   10001
	**   11111
	*/
	static const t_wall_coord_case	cases[] = {
		{"open space (1,1)",       1, 1, false},
		{"open space (2,2)",       2, 2, false},
		{"wall top-left (0,0)",    0, 0, true},
		{"wall top-right (4,0)",   4, 0, true},
		{"wall bottom-left (0,4)", 0, 4, true},
		{"out of bounds x=-1",    -1, 0, true},
		{"out of bounds y=-1",     0, -1, true},
		{"out of bounds x=5",      5, 0, true},
		{"out of bounds y=5",      0, 5, true},
	};
	int		passed;
	bool	result;
	size_t	i;

	passed = 0;
	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		result = is_wall_or_space_on_coords(map, cases[i].x, cases[i].y);
		if (result == cases[i].expected)
		{
			putsuccess(cases[i].name);
			passed++;
		}
		else
		{
			puterror(cases[i].name);
			dprintf(STDERR_FILENO, "  expected %d, got %d\n",
				cases[i].expected, result);
		}
		i++;
	}
	return (passed == (int)(sizeof(cases) / sizeof(cases[0])));
}

static int	run_is_wall_cases(t_map *map)
{
	/*
	** Inside a cell: checks floor(start).
	** On an x-edge: adjusts x by ray direction.
	** On a y-edge: adjusts y by ray direction.
	*/
	static const t_is_wall_case	cases[] = {
		{"mid-cell open (2.5,2.5) east",
			{2.5f, 2.5f}, { 1,  0}, false},
		{"mid-cell wall (0.5,0.5) east",
			{0.5f, 0.5f}, { 1,  0}, true},
		{"x-edge (3.0,2.5) east -> cell (3,2) open",
			{3.0f, 2.5f}, { 1,  0}, false},
		{"x-edge (4.0,2.5) east -> cell (4,2) wall",
			{4.0f, 2.5f}, { 1,  0}, true},
		{"x-edge (1.0,2.5) west -> cell (0,2) wall",
			{1.0f, 2.5f}, {-1,  0}, true},
		{"y-edge (2.5,1.0) north -> cell (2,0) wall",
			{2.5f, 1.0f}, { 0, -1}, true},
		{"y-edge (2.5,3.0) south -> cell (2,3) open",
			{2.5f, 3.0f}, { 0,  1}, false},
	};
	int		passed;
	bool	result;
	size_t	i;

	passed = 0;
	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		result = is_wall(cases[i].start, cases[i].dir, map);
		if (result == cases[i].expected)
		{
			putsuccess(cases[i].name);
			passed++;
		}
		else
		{
			puterror(cases[i].name);
			dprintf(STDERR_FILENO, "  expected %d, got %d\n",
				cases[i].expected, result);
		}
		i++;
	}
	return (passed == (int)(sizeof(cases) / sizeof(cases[0])));
}

/*
** run_corner_cases — exhaustive test of the exact-integer-corner branch
** (is_on_x && is_on_y) inside is_wall().
**
** At an integer corner (cx, cy) there are four surrounding cells.
** The ray must enter the ONE cell that its direction points into:
**
**   NW direction (ux<0, uy<0)  → cell (cx-1, cy-1)   [already worked]
**   NE direction (ux>0, uy<0)  → cell (cx,   cy-1)   [BUG: skipped]
**   SW direction (ux<0, uy>0)  → cell (cx-1, cy  )   [BUG: skipped]
**   SE direction (ux>0, uy>0)  → cell (cx,   cy  )   [already worked]
**
** Map A — wall pillars at (2,1) and (2,3), open everywhere else:
**   11111  y=0
**   10101  y=1  <- wall at (2,1)
**   10001  y=2
**   10101  y=3  <- wall at (2,3)
**   11111  y=4
**
** Wall-hit cases (surrounding cells chosen so only the target cell is a wall):
**   NE from (2.0,2.0): NE=(2,1)=wall, NW=(1,1)=open, SE=(2,2)=open, SW=(1,2)=open
**   NW from (3.0,2.0): NW=(2,1)=wall, NE=(3,1)=open, SE=(3,2)=open, SW=(2,2)=open
**   SE from (2.0,3.0): SE=(2,3)=wall, NW=(1,2)=open, NE=(2,2)=open, SW=(1,3)=open
**   SW from (3.0,3.0): SW=(2,3)=wall, NW=(2,2)=open, NE=(3,2)=open, SE=(3,3)=open
**
** Map B — fully open interior (regression: fix must not break open corners):
**   All four directions from (2.0,2.0) must return false.
*/
typedef struct s_corner_case
{
	const char	*name;
	t_coords	pos;
	t_vec2		dir;
	bool		expected;
}	t_corner_case;

static int	run_corner_cases(void)
{
	char	*rows_a[] = {
		"11111",
		"10101",
		"10001",
		"10101",
		"11111",
		NULL
	};
	char	*rows_b[] = {
		"11111",
		"10001",
		"10001",
		"10001",
		"11111",
		NULL
	};
	/*
	** Diagonal unit vectors (normalised ±1/√2 ≈ ±0.7071).
	** The exact magnitude does not matter — only the sign of each component
	** is used by get_block_coord to choose the target cell.
	*/
	static const t_corner_case	cases_a[] = {
		{"NE (2.0,2.0)→(2,1) wall [BUG if false]",
			{2.0f, 2.0f}, { 0.7071f, -0.7071f}, true},
		{"NW (3.0,2.0)→(2,1) wall",
			{3.0f, 2.0f}, {-0.7071f, -0.7071f}, true},
		{"SE (2.0,3.0)→(2,3) wall",
			{2.0f, 3.0f}, { 0.7071f,  0.7071f}, true},
		{"SW (3.0,3.0)→(2,3) wall [BUG if false]",
			{3.0f, 3.0f}, {-0.7071f,  0.7071f}, true},
	};
	static const t_corner_case	cases_b[] = {
		{"NE (2.0,2.0) open interior → false",
			{2.0f, 2.0f}, { 0.7071f, -0.7071f}, false},
		{"NW (2.0,2.0) open interior → false",
			{2.0f, 2.0f}, {-0.7071f, -0.7071f}, false},
		{"SE (2.0,2.0) open interior → false",
			{2.0f, 2.0f}, { 0.7071f,  0.7071f}, false},
		{"SW (2.0,2.0) open interior → false",
			{2.0f, 2.0f}, {-0.7071f,  0.7071f}, false},
	};
	t_map	map_a;
	t_map	map_b;
	int		passed;
	bool	result;
	size_t	i;

	map_a.data = rows_a;
	map_a.height = 5;
	map_a.width = 5;
	map_b.data = rows_b;
	map_b.height = 5;
	map_b.width = 5;
	passed = 0;
	i = 0;
	while (i < sizeof(cases_a) / sizeof(cases_a[0]))
	{
		result = is_wall(cases_a[i].pos, cases_a[i].dir, &map_a);
		if (result == cases_a[i].expected)
		{
			putsuccess(cases_a[i].name);
			passed++;
		}
		else
		{
			puterror(cases_a[i].name);
			dprintf(STDERR_FILENO, "  expected %d, got %d\n",
				cases_a[i].expected, result);
		}
		i++;
	}
	i = 0;
	while (i < sizeof(cases_b) / sizeof(cases_b[0]))
	{
		result = is_wall(cases_b[i].pos, cases_b[i].dir, &map_b);
		if (result == cases_b[i].expected)
		{
			putsuccess(cases_b[i].name);
			passed++;
		}
		else
		{
			puterror(cases_b[i].name);
			dprintf(STDERR_FILENO, "  expected %d, got %d\n",
				cases_b[i].expected, result);
		}
		i++;
	}
	return (passed == (int)(sizeof(cases_a) / sizeof(cases_a[0])
			+ sizeof(cases_b) / sizeof(cases_b[0])));
}

int	main(void)
{
	char	*rows[] = {
		"11111",
		"10001",
		"10001",
		"10001",
		"11111",
		NULL
	};
	t_map	map;
	int		all_ok;

	map.data = rows;
	map.height = 5;
	map.width = 5;
	all_ok = run_coord_cases(&map);
	all_ok &= run_is_wall_cases(&map);
	all_ok &= run_corner_cases();
	if (all_ok)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
